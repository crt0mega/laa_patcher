/*
 * laa_patcher.c
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
#include <stdbool.h>
#include <string.h>
#include "help.h"
#include "patch.h"

#define VERSION 0.1



int main(int argc, char **argv)
{
	// Introduce yerself
	
	printf("laa_patcher v%g (c) 2020 by crt0mega\n", VERSION, argc);
	
	if (argc == 1)
	{
		help();
		return 0;
	}
	
	char filename[strlen(argv[1])];
	strcpy(filename, argv[1]);
	
	printf("\nPatching %s ...\n", filename);
	
	if (ispe(filename))
	{
		printf("- %s is a PE binary...\n", filename);
	}
	
	else
	{
		printf("- %s is no PE binary, aborting.\n", filename);
		return 1;
	}
	
	if (ispatched(filename))
	{
		printf("- %s is already aware of large addresses, unpatching.\n", filename);
		//return 1;
	}
		
	// Let's get busy
	
	bool success;
	
	success = patch(filename);
	
	if (success == true)
	{
		printf("- %s successfully patched.\n", filename);
		return 0;
	}	
	
	else
	{
		printf("- Error while patching %s.\n", filename);
		return 1;
	}
	
}
