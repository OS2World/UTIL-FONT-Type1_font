/*
Simple progam to extract font information for X from
postscript type 1 font files.

This program is usefull, if (better) made type1inst perl proggam is not runnable.

Use:
Font file should be feede into Standard input.
1st parameter should be font file name.

example:
extract courier.pbf <courier.pbf

This code is in public domain.
Please copy source along with executable, so that others may
improve / correct code.

Author:
 Lauri Paatero
 Lauri.Paatero@paatero.pp.fi

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

unsigned char getASCII( void )
{
    int ch = getc(stdin);
    if (ch==-1)
        exit(1);
    if (ch=='/' || ch=='(' || ch==')')
        return ch;
    if (ch>='A' && ch<='Z')
        return ch;
    if (ch>='a' && ch<='z')
        return ch;
    if (ch>='0' && ch<='9')
        return ch;
    return ' ';
}

void getWord( unsigned char *buf, int maxLen )
{
    unsigned char ch;
    do {
        ch=getASCII();
    } while (ch==' ' || ch=='(' || ch==')');

    do {
        *buf = ch;
        buf++;
        ch=getASCII();
    } while (ch != ' ' && maxLen-->0 && ch!='/' && ch!=')' && ch!='(');
    *buf = '\0' ;
}

void getString( unsigned char *buf, int maxLen )
{
    unsigned char ch;
    int par = 1;
    while ((ch=getASCII()) == ' ') {
    }

    if (ch!='(')
        return;

    while ((ch=getASCII()) == ' ') {
    }

    if (ch==')')
        return;

    do {
        *buf = ch;
        buf++;
        ch=getASCII();
        if (ch==')')
            par--;
        else if (ch=='(')
            par++;
    } while (maxLen-->0 && par>0);
    *buf = '\0' ;
}

char *mapFoundry[][2] = {    "Adobe", "adobe",
    "adobe", "adobe",
    "allied corporation", "allied",
    "publishers' paradise", "paradise",
    "bigelow & holmes", "b&h",
    "bitstream", "bitstream",
    "corel corporation", "corel",
    "international typeface corporation", "itc",
    "ibm", "ibm",
    "letraset", "letraset",
    "monotype corporation", "monotype",
    "softmaker", "softmaker",
    "urw", "urw",
    "jonathan brecher", "brecher",
    "brendel informatik", "brendel",
    "a. carr", "carr",
    "fontbank", "fontbank",
    "hershey", "hershey",
    "a.s.meit", "meit",
    "andrew s. meit", "meit",
    "s.g. moye", "moye",
    "s. g. moye", "moye",
    "d. rakowski", "rakowski",
    "david rakowski", "rakowski",
    "reasonable solutions", "reasonable",
    "southern software", "southern",
    "title wave", "titlewave",
    "zsoft", "zsoft",
    "digiteyes multimedia", "digiteyes",
    "mwsoft", "mwsoft",
    "macromind", "macromind",
    "three islands press", "3ip",
    "hank gillette", "gillette",
    "doug miles", "miles",
    "richard mitchell", "mitchell",
    NULL, NULL
};

char *mapWeight[][2] = {
    "book", "book",
    "demibold", "demibold",
    "semibold", "demibold",
    "demi", "demibold",
    "semi", "demibold",
    "extrabold", "extrabold",
    "boldface", "bold",
    "bold", "bold",
    "heavyface", "heavyface",
    "heavy", "heavy",
    "ultrablack", "ultrablack",
    "extrablack", "extrablack",
    "ultra", "ultra",
    "black", "black",
    "extralight", "extralight",
    "light", "light",
    "thin", "thin",
    "super", "super",
    "thin", "thin",
    "light", "light",
    "semi", "demi",
    "bold", "bold",
    "heavy", "heavy",
    "black", "black",
    "normal", "medium",
    "regular", "regular",
    "roman", "regular",
    NULL, NULL
};

char *mapSlant[][2] = {
    " italic", "i",
    " roman", "r",
    " regular", "r",
    " cursive", "i",
    " kursiv", "i",
    " oblique", "o",
    " obl", "o",
    " slanted", "o",
    " upright", "r",
    " inclined", "i",
    NULL, NULL
};

char *mapWidth[][2] = {
    " extracondensed", "extracondensed",
    " condensed", "condensed",
    " cond", "condensed",
    " sans", "sans",
    " wide", "wide",
    " cn", "condensed",
    " narrow", "narrow",
    " extracompressed", "extracompressed",
    " compressed", "compressed",
    " extraextended", "extraextended",
    " extended", "extended",
    " expanded", "expanded",
    " normal", "normal",
    NULL, NULL
};

char *mapFixed[][2] = {
    { "false", "p" },
    { "true", "m" },
    { NULL, NULL }
};


void ConvertBuf( unsigned char *buf, char *table[][2] )
{
    int ct;
    for (ct=0; table[ct][0]!=NULL; ct++) {
        if (stricmp( buf, table[ct][0] )==0) {
            strcpy( buf, table[ct][1] );
            return;
        }
    }
}

void findMatch( unsigned char *buf, unsigned char *res, char *table[][2] )
{
    int ct;
    for (ct=0; table[ct][0]!=NULL; ct++) {
        if (strstr( (char*)buf, table[ct][0] )!=NULL) {
            strcpy( res, table[ct][1] );
//            return;   Keet table priority order revered
        }
    }
}

void lower( char *buf  )
{
    int ct;
    for (ct=0; buf[ct]!=0; ct++) {
        buf[ct] = tolower( buf[ct] );
    }
}

void main(int argc, char *argv[])
{
    unsigned char buf[100];
    unsigned char notice[100];
    unsigned char fullName[100];
    unsigned char familyName[100];
    unsigned char weigth[100];
    unsigned char italic[100];
    unsigned char fixed[100];

    unsigned char foundry[100]  = "";
    unsigned char slant[100]  = "r";
    unsigned char width[100]  = "normal";


    for (;;) {
        getWord( buf, 99 );
        if (stricmp( buf, "/Notice" )==0)
            getString( notice, 99 );        else if (stricmp( buf, "/FullName" )==0)
            getString( fullName, 99 );
        else if (stricmp( buf, "/FamilyName" )==0)
            getString( familyName, 99 );
        else if (stricmp( buf, "/Weight" )==0)
            getString( weigth, 99 );
        else if (stricmp( buf, "/ItalicAngle" )==0)
            getWord( italic, 99 );
        else if (stricmp( buf, "/isFixedPitch" )==0)
            getWord( fixed, 99 );
        else if (stricmp( buf, "eexec" )==0)
            break;
        else {
//            if (buf[0]=='/')
//                printf( "%s\n", buf );
        }

    }


    lower( weigth );
    ConvertBuf( weigth, mapWeight );
    lower( fixed );
    ConvertBuf( fixed, mapFixed );
    if (atoi(italic)!=0)
        strcpy( slant, "i" );

    if (argc>1) {
        strcpy( buf, argv[1] );
        lower( buf );
    } else
        strcpy( buf, "" );

    lower( notice );
    findMatch( notice, foundry, mapFoundry );

    // Lets dig out as much as possible from fullName
    lower( fullName );
    findMatch( fullName, slant, mapSlant );
    findMatch( fullName, width, mapWidth );

    lower( familyName );

    printf( "%s -%s-%s-%s-%s-%s--0-0-0-0-%s-0-iso8859-1\n",
            buf, foundry, familyName, weigth, slant, width, fixed );

}
