/*
 * help.c
 * 
 * Copyright 2020 crt0mega <crt0mega@c-r-t.tk>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>

void help()
{
	printf("\nUsage:\nlaa_patcher <some.exe>\n"
		"This Program sets or unsets the LARGE_ADDRESS_AWARE flag on "
		"32 Bit PE Executables.\n");
}
