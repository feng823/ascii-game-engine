/*
** This source file is part of MY-BASIC
**
** For the latest info, see http://code.google.com/p/ascii-game-engine/
**
** Copyright (c) 2011 Tony & Tony's Toy Game Development Team
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of
** this software and associated documentation files (the "Software"), to deal in
** the Software without restriction, including without limitation the rights to
** use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
** the Software, and to permit persons to whom the Software is furnished to do so,
** subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
** FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
** COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
** IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
** CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "ageutil.h"

#pragma comment(lib, "winmm.lib")

u32 get_tick_count(void) {
	return timeGetTime();
}

void sys_sleep(s32 _time) {
	Sleep(_time);
}

s32 freadln(FILE* fp, Str* buf) {
	s32 result = 0;
	s8 ch = 0;
	long ft = 0;

	assert(fp && buf);

	ch = (s8)fgetc(fp);
	while(ch != EOF && ch != '\r' && ch != '\n') {
		if(ch != EOF) {
			(*buf)[result++] = ch;
		}
		ch = (s8)fgetc(fp);
	}
	(*buf)[result] = '\0';

	if(ch != EOF) {
		ft = ftell(fp);
		ch = (s8)fgetc(fp);
		if(ch != '\n') {
			fseek(fp, ft, 0);
		}
	}

	return result;
}
