// flnfc_common.cxx -- common string subs for Fl_Native_File_Chooser
//
// Copyright 2004 by Greg Ercolano.
// ----------------------------------------------------------------------------
// Copyright (C) 2014
//              David Freese, W1HKJ
//
// This file is part of flmsg
//
// flrig is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// flrig is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#include <string.h>

// COPY A STRING WITH 'new'
//    Value can be NULL
//
static char *strnew(const char *val) {
    if ( val == NULL ) return(NULL);
    char *s = new char[strlen(val)+1];
    strcpy(s, val);
    return(s);
}

// FREE STRING CREATED WITH strnew(), NULLS OUT STRING
//    Value can be NULL
//
static char *strfree(char *val) {
    if ( val ) delete [] val;
    return(NULL);
}

#ifndef __WOE32__
// 'DYNAMICALLY' APPEND ONE STRING TO ANOTHER
//    Returns newly allocated string, or NULL 
//    if s && val == NULL.
//    's' can be NULL; returns a strnew(val).
//    'val' can be NULL; s is returned unmodified.
//
//    Usage:
//	char *s = strnew("foo");	// s = "foo"
//      s = strapp(s, "bar");		// s = "foobar"
//
static char *strapp(char *s, const char *val) {
    if ( ! val ) {
        return(s);              // Nothing to append? return s
    }
    if ( ! s ) {
        return(strnew(val));    // New string? return copy of val
    }
    char *news = new char[strlen(s)+strlen(val)+1];
    strcpy(news, s);
    strcat(news, val);
    delete [] s;		// delete old string
    return(news);		// return new copy
}
#endif

// APPEND A CHARACTER TO A STRING
//     This does NOT allocate space for the new character.
//
static void chrcat(char *s, char c) {
    char tmp[2] = { c, '\0' };
    strcat(s, tmp);
}
