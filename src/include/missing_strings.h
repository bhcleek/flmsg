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

/*
 * "$Id: flstring.h 4660 2005-11-27 14:45:48Z mike $"
 *
 * Common string header file for the Fast Light Tool Kit (FLTK).
 * versions < 1.3.x
 *
 * Copyright 1998-2005 by Bill Spitzak and others.
 */

#ifndef flstring_h
#  define flstring_h

#include <config.h>

// versions of FLTK < 1.3.2 do not contain fl_string
#if (FLMSG_FLTK_API_MAJOR == 1 && FLMSG_FLTK_API_MINOR < 3 ) || \
    (FLMSG_FLTK_API_MAJOR == 1 && FLMSG_FLTK_API_MINOR == 3 && FLMSG_FLTK_API_PATCH < 1)

#  include <FL/Fl_Export.H>
#  include <config.h>
#  include <stdio.h>
#  include <stdarg.h>
#  include <string.h>

#  ifdef HAVE_STRINGS_H
#    include <strings.h>
#  endif /* HAVE_STRINGS_H */

#  include <ctype.h>

/*
 * Apparently Unixware defines "index" to strchr (!) rather than
 * providing a proper entry point or not providing the (obsolete)
 * BSD function.  Make sure index is not defined...
 */

#  ifdef index
#    undef index
#  endif /* index */

#  if defined(WIN32) && !defined(__CYGWIN__)
#    define strcasecmp(s,t)	_stricmp((s), (t))
#    define strncasecmp(s,t,n)	_strnicmp((s), (t), (n))
// Visual C++ 2005 incorrectly displays a warning about the use of POSIX APIs
// on Windows, which is supposed to be POSIX compliant...  Some of these functions
// are also defined in ISO C99...
#  define strdup _strdup
#  define unlink _unlink
#  elif defined(__EMX__)
#    define strcasecmp(s,t)	stricmp((s), (t))
#    define strncasecmp(s,t,n)	strnicmp((s), (t), (n))
#  endif /* WIN32 */

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

/*
 * MetroWerks' CodeWarrior put thes "non-standard" functions in
 * <extras.h> which unfortunatly does not play well otherwise
 * when included - to be resolved...
 */

#  if defined(__APPLE__) && defined(__MWERKS__) && defined(_MSL_USING_MW_C_HEADERS)
int strcasecmp(const char*,const char*);
int strncasecmp(const char*,const char*,int);
char *strdup(const char*);
#  endif

FL_EXPORT extern int fl_snprintf(char *, size_t, const char *, ...);
#  if !HAVE_SNPRINTF
#    define snprintf fl_snprintf
#  endif /* !HAVE_SNPRINTF */

FL_EXPORT extern int fl_vsnprintf(char *, size_t, const char *, va_list ap);
#  if !HAVE_VSNPRINTF
#    define vsnprintf fl_vsnprintf
#  endif /* !HAVE_VSNPRINTF */

/*
 * strlcpy() and strlcat() are some really useful BSD string functions
 * that work the way strncpy() and strncat() *should* have worked.
 */

FL_EXPORT extern size_t fl_strlcat(char *, const char *, size_t);
#  if !HAVE_STRLCAT
#    define strlcat fl_strlcat
#  endif /* !HAVE_STRLCAT */

FL_EXPORT extern size_t fl_strlcpy(char *, const char *, size_t);
#  if !HAVE_STRLCPY
#    define strlcpy fl_strlcpy
#  endif /* !HAVE_STRLCPY */

#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* < FLTK < 1.3.0 */

#endif /* !flstring_h */
 
