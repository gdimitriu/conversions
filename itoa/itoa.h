/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of itoa library.
	It is the definition of int to ascii function for unix.

    Itoa library is free software; you can redistribute it 
	and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 2 of 
	the License, or (at your option) any later version.

    Itoa library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with itoa library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
#ifndef _HAVE_itoa_
#define _HAVE_itoa_ 1
void itoa(int value,char *str,int base);
#endif