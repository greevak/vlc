/*****************************************************************************
 * charset.h: Unicode UTF-8 wrappers function
 *****************************************************************************
 * Copyright (C) 2003-2005 the VideoLAN team
 * Copyright © 2005-2006 Rémi Denis-Courmont
 * $Id$
 *
 * Author: Rémi Denis-Courmont <rem # videolan,org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef __VLC_CHARSET_H
#define __VLC_CHARSET_H 1

#include <stdarg.h>
#include <sys/types.h>
#include <dirent.h>

VLC_EXPORT( void, LocaleFree, ( const char * ) );
VLC_EXPORT( char *, FromLocale, ( const char * ) );
VLC_EXPORT( char *, FromLocaleDup, ( const char * ) );
VLC_EXPORT( char *, ToLocale, ( const char * ) );

VLC_EXPORT( int, utf8_open, ( const char *filename, int flags, mode_t mode ) );
VLC_EXPORT( FILE *, utf8_fopen, ( const char *filename, const char *mode ) );
VLC_EXPORT( DIR *, utf8_opendir, ( const char *dirname ) );
VLC_EXPORT( char *, utf8_readdir, ( void *dir ) );
VLC_EXPORT( int, utf8_scandir, ( const char *dirname, char ***namelist, int (*select)( const char * ), int (*compar)( const char **, const char ** ) ) );

#ifdef WIN32
# define stat _stati64
#endif

VLC_EXPORT( int, utf8_stat, ( const char *filename, struct stat *buf ) );
VLC_EXPORT( int, utf8_lstat, ( const char *filename, struct stat *buf ) );
VLC_EXPORT( int, utf8_mkdir, ( const char *filename ) );

VLC_EXPORT( int, utf8_vfprintf, ( FILE *stream, const char *fmt, va_list ap ) );
VLC_EXPORT( int, utf8_fprintf, ( FILE *, const char *, ... ) );

VLC_EXPORT( char *, EnsureUTF8, ( char * ) );
VLC_EXPORT( const char *, IsUTF8, ( const char * ) );

#ifdef WIN32
static inline char *FromWide (const wchar_t *wide)
{
    size_t len = WideCharToMultiByte (CP_UTF8, 0, wide, -1, NULL, 0, NULL, NULL);
    if (len == 0)
        return NULL;

    char *out = (char *)malloc (len);

    WideCharToMultiByte (CP_UTF8, 0, wide, -1, out, len, NULL, NULL);
    return out;
}
#endif

VLC_INTERNAL( char *, vlc_fix_readdir, ( const char * ) );
VLC_INTERNAL( vlc_bool_t, vlc_current_charset, ( char ** ) );

VLC_EXPORT( const char *, GetFallbackEncoding, ( void ) );

VLC_INTERNAL( double, i18n_strtod, ( const char *, char ** ) );
VLC_INTERNAL( double, i18n_atof, ( const char * ) );
VLC_EXPORT( double, us_strtod, ( const char *, char ** ) );
VLC_EXPORT( double, us_atof, ( const char * ) );

#endif
