/*
** This source file is part of AGE
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

#include "logic.h"
#include "game.h"
#include "state.h"
#include "renderer.h"

typedef struct MessageContext {
	Ptr receiver;
	Ptr sender;
	u32 msg;
	u32 lparam;
	u32 wparam;
	Ptr extra;
} MessageContext;

static MessageContext lastMsg;

static s32 _broadcast_message_to_sprite(Ptr _data, Ptr _extra) {
	s32 result = 0;

	Sprite* spr = (Sprite*)_data;
	send_message_to_sprite(spr, lastMsg.receiver, lastMsg.msg, lastMsg.lparam, lastMsg.wparam, lastMsg.extra);

	return result;
}

BoardUserdata* create_board_userdata(void) {
	BoardUserdata* result = 0;

	result = AGE_MALLOC(BoardUserdata);

	return result;
}

void destroy_board_userdata(Ptr _ptr) {
	BoardUserdata* ud = (BoardUserdata*)_ptr;
	assert(ud);
	AGE_FREE(ud);
}

PlayerUserdata* create_player_userdata(void) {
	PlayerUserdata* result = 0;

	result = AGE_MALLOC(PlayerUserdata);

	return result;
}

void destroy_player_userdata(Ptr _ptr) {
	PlayerUserdata* ud = (PlayerUserdata*)_ptr;
	assert(ud);
	AGE_FREE(ud);
}

s32 on_ctrl_for_sprite_main_player(Ptr _obj, const Str _name, s32 _elapsedTime, u32 _lparam, u32 _wparam, Ptr _extra) {
	s32 result = 0;

	if(is_key_down(AGE_IPT, 0, KC_LEFT)) {
		send_message_to_sprite(game()->main, 0, MSG_MOVE, DIR_LEFT, 0, 0);
	} else if(is_key_down(AGE_IPT, 0, KC_RIGHT)) {
		send_message_to_sprite(game()->main, 0, MSG_MOVE, DIR_RIGHT, 0, 0);
	}

	return result;
}

s32 on_ctrl_for_sprite_board(Ptr _obj, const Str _name, s32 _elapsedTime, u32 _lparam, u32 _wparam, Ptr _extra) {
	s32 result = 0;

	return result;
}

s32 on_msg_proc_for_canvas(Ptr _receiver, Ptr _sender, u32 _msg, u32 _lparam, u32 _wparam, Ptr _extra) {
	s32 result = 0;
	Canvas* cvs = (Canvas*)_receiver;
	BoardUserdata* ud = 0;
	Sprite* b = 0;
	s32 i = 0;

	lastMsg.receiver = _receiver;
	lastMsg.sender = _sender;
	lastMsg.msg = _msg;
	lastMsg.lparam = _lparam;
	lastMsg.wparam = _wparam;
	lastMsg.extra = _extra;

	assert(cvs && cvs->sprites);

	switch(_msg) {
		case MSG_BOARD_UP:
			ht_foreach(cvs->sprites, _broadcast_message_to_sprite);
			for(i = 0; i < game()->boardCount; ++i) {
				b = game()->boardPool[i];
				ud = (BoardUserdata*)b->userdata.data;
				assert(ud);
				if(ud->drop) {
					game()->remove_board(b);
				}
			}
			break;
	}

	return result;
}

s32 on_msg_proc_for_sprite_main_player(Ptr _receiver, Ptr _sender, u32 _msg, u32 _lparam, u32 _wparam, Ptr _extra) {
	s32 result = 0;

	return result;
}

s32 on_msg_proc_for_sprite_board(Ptr _receiver, Ptr _sender, u32 _msg, u32 _lparam, u32 _wparam, Ptr _extra) {
	s32 result = 0;

	return result;
}

s32 on_playing_for_sprite_main_player(struct Canvas* _cvs, struct Sprite* _spr, const Str _begin, const Str _end, s32 _currIdx) {
	s32 result = 0;

	return result;
}

s32 on_playing_for_sprite_board(struct Canvas* _cvs, struct Sprite* _spr, const Str _begin, const Str _end, s32 _currIdx) {
	s32 result = 0;

	return result;
}

void on_removing_for_sprite_main_player(Ptr _handlerObj, struct Canvas* _cvs, struct Sprite* _spr) {
}

void on_removing_for_sprite_board(Ptr _handlerObj, struct Canvas* _cvs, struct Sprite* _spr) {
}

void on_collide_for_sprite_main_player(struct Canvas* _cvs, struct Sprite* _spr, s32 _px, s32 _py) {
	Pixel* pixelc = 0;
	PlayerUserdata* ud = 0;
	Sprite* bd = 0;
	s32 i = 0;
	//s32 k = 0;
	s32 x = 0;
	s32 y = 0;
	//s32 fx = 0;
	//s32 fy = 0;
	//s8 b = 0;
	//bl ob = FALSE;

	assert(_px >= 0 && _px < CANVAS_WIDTH && _py >= 0 && _py < CANVAS_HEIGHT);

	pixelc = &_cvs->pixels[_px + _py * _cvs->size.w];
	ud = (PlayerUserdata*)(_spr->userdata.data);
	ud->onBoard[0] = '\0';
	for(i = 0; i < pixelc->frameCount; ++i) {
		bd = pixelc->ownerFrames[i]->parent;
		if(bd != _spr) {
			//fx = _px - _spr->position.x;
			//fy = _py - _spr->position.y;
			//k = _spr->timeLine.currentFrame;
			//b = _spr->timeLine.frames[k].tex[fx + fy * _spr->frameSize.w].brush;

			//if(b == game()->footBrush) {
				assert(strlen(_spr->name) + 1 < _countof(ud->onBoard));
				sprintf(ud->onBoard, bd->name);
				//ob = TRUE;
				break;
			//}
		}
	}

	//if(!ob) {
	//	set_sprite_position(_cvs, _spr, _spr->lastFramePosition.x, _spr->position.y);
	//}
}

void on_collide_for_sprite_board(struct Canvas* _cvs, struct Sprite* _spr, s32 _px, s32 _py) {
}

void on_update_for_sprite_main_player(struct Canvas* _cvs, struct Sprite* _spr, s32 _elapsedTime) {
	PlayerUserdata* ud = 0;
	Sprite* bd = 0;
	s32 x = 0;
	s32 y = 0;
	s32 bx = 0;
	s32 by = 0;

	assert(_cvs && _spr);

	ud = (PlayerUserdata*)(_spr->userdata.data);
	assert(ud);
	ud->time += _elapsedTime;
	if(ud->time >= ud->fallTime) {
		ud->time -= ud->fallTime;
		get_sprite_position(_cvs, _spr, &x, &y);
		if(ud->onBoard[0]) {
			bd = get_sprite_by_name(_cvs, ud->onBoard);
			if(bd) {
				get_sprite_position(_cvs, bd, &bx, &by);
				by = by - _spr->frameSize.h + 1;
				set_sprite_position(_cvs, _spr, x, by);
				if(by + _spr->frameSize.h <= GAME_AREA_TOP) {
					_asm nop
					// TODO
				}
			}
		} else {
			++y;
			set_sprite_position(_cvs, _spr, x, y);
			if(y > GAME_AREA_BOTTOM) {
				// TODO
			}
		}
	}
	ud->onBoard[0] = '\0';
}

void on_update_for_sprite_board(struct Canvas* _cvs, struct Sprite* _spr, s32 _elapsedTime) {
}

s32 on_msg_proc_for_sprite_board_up(Ptr _receiver, Ptr _sender, u32 _msg, u32 _lparam, u32 _wparam, Ptr _extra) {
	s32 result = 0;
	Sprite* spr = (Sprite*)_receiver;
	Canvas* cvs = (Canvas*)_sender;
	s32 x = 0;
	s32 y = 0;

	assert(_msg == MSG_BOARD_UP);

	get_sprite_position(cvs, spr, &x, &y);
	--y;
	if(y < -spr->frameSize.h) {
		game()->drop_board(spr);
	} else {
		set_sprite_position(cvs, spr, x, y);
	}

	return result;
}

s32 on_msg_proc_for_sprite_main_player_move(Ptr _receiver, Ptr _sender, u32 _msg, u32 _lparam, u32 _wparam, Ptr _extra) {
	s32 result = 0;
	Sprite* spr = (Sprite*)_receiver;
	s32 x = 0;
	s32 y = 0;

	assert(_msg == MSG_MOVE);

	get_sprite_position(spr->owner, spr, &x, &y);
	switch(_lparam) {
		case DIR_LEFT:
			--x;
			if(x <= GAME_AREA_LEFT) {
				x = GAME_AREA_LEFT + 1;
			}
			break;
		case DIR_RIGHT:
			++x;
			if(x + spr->frameSize.w - 1 >= GAME_AREA_RIGHT) {
				x = GAME_AREA_RIGHT - spr->frameSize.w;
			}
			break;
		default:
			assert("Unknow direction");
			break;
	}
	set_sprite_position(spr->owner, spr, x, y);

	return result;
}
