/*
 * patch.c
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
#include <stdint.h>

#define IS_LAA 0x0020

bool ispe(char *filename)
{
	FILE *pFile;
	int16_t header;
	int32_t peloc;
	int32_t peheader;
	
	pFile = fopen(filename, "rb");
	fread(&header, sizeof(header), 1, pFile);
		
	if (header != 0x5a4d) //Check presence of MZ magic bytes
	{
		fclose(pFile);
		return false;
	}
	
	fseek(pFile, 0x3c, SEEK_SET);
	fread(&peloc, sizeof(peloc), 1, pFile); //Get PE header location
	
	fseek(pFile, peloc, SEEK_SET);
	fread(&peheader, sizeof(peheader), 1, pFile);
	
	if (peheader != 0x4550) // Check presence of PE magic bytes
	{
		fclose(pFile);
		return false;
	}
	
	fclose(pFile);
	return true;
}

bool ispatched(char *filename)
{
	FILE *pFile;
	int32_t peloc;
	int32_t peheader;
	int16_t laa;
	
	if (!ispe(filename))
	{
		printf("How did we even get here?!");
		return false;
	}
	
	pFile = fopen(filename, "rb");
	
	fseek(pFile, 0x3c, SEEK_SET);
	fread(&peloc, sizeof(peloc), 1, pFile);
	
	fseek(pFile, peloc, SEEK_SET); // Seek to PE Location and
	fread(&peheader, sizeof(peheader), 1, pFile); // Fetch header
	
	if (peheader != 0x4550)
	{
		printf("How the hell did we even geht here?!");
		return false;
	}
	
	fseek(pFile, 0x12, SEEK_CUR); // Seek to characteristics
	fread(&laa, sizeof(laa), 1, pFile); // Read characteristics
	
	fclose(pFile);
	
	if ((laa & IS_LAA) == IS_LAA)
	{
		return true;
	}
	
	return false;
}

bool patch(char *filename)
{
	FILE *pFile;
	int32_t peloc;
	int32_t peheader;
	int16_t laa;
	
	if (!ispe(filename))
	{
		printf("How did we even get here?!\n");
		return false;
	}
	
	pFile = fopen(filename, "r+b");
	
	fseek(pFile, 0x3c, SEEK_SET);
	fread(&peloc, sizeof(peloc), 1, pFile);
	
	fseek(pFile, peloc, SEEK_SET); // Seek to PE Location and
	fread(&peheader, sizeof(peheader), 1, pFile); // Fetch header
	
	if (peheader != 0x4550)
	{
		printf("How the hell did we even geht here?!\n");
		return false;
	}
	
	fseek(pFile, 0x12, SEEK_CUR); // Seek to characteristics
	fread(&laa, sizeof(laa), 1, pFile); // Read characteristics
	
	int16_t setlaa;
	
	if ((laa & IS_LAA) == IS_LAA)
	{
		setlaa=laa&~IS_LAA;
	}
	
	else
	{
		setlaa=laa|IS_LAA;
	}
			
	fseek(pFile, -sizeof(laa), SEEK_CUR); // Seek back
	fwrite(&setlaa, 1, sizeof(setlaa), pFile); // Write new value
	
	fclose(pFile);
	
	return true;	
	
}
