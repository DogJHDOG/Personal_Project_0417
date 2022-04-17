#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES	1
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <bangtal.h>
#include <string.h>
#include <string>

SceneID room1;
ObjectID cha, fence, fence2, guard1, guard2, door,timerbox;

struct POS {
	int x, y;
};
const POS positions[12] = {
	{0, 450}, {150, 450}, {300, 450},
	{0, 300}, {150, 300}, {300, 300},
	{0, 150}, {150, 150}, {300, 150},
	{0, 00}, {150, 00}, {300, 00}
};

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
	//물체 생성하기
	ObjectID object = createObject(image);
	//위치보이기
	locateObject(object, scene, x, y);
	//보이기
	if (shown == true) {
		showObject(object);
	}
	return object;
}

#include <bangtal.h>
TimerID guardtimer, traptimer, timer1, timer2, timer3;
SceneID startpage,scene,scene2,scene3,endpage;
ObjectID ball,ball2,ball3,ball3r,ball3l,ball3d, start, starts3, starts4;
ObjectID trap1, trap2, trap3, trap4;
ObjectID up, down, rights, lefts;
ObjectID wall1, wall2, wall3, wall4;
ObjectID gameexit, restart, reend, gameexit2, restart2, reend2, gameexit3, restart3, reend3;


int click3x = 0;
int click3y = 0;


int x = 1100, y = 0;
int x2 = 1100, y2 = 720;
int x3 = 620, y3 = 0;

int guard1x = 500;
int dx = 0, dy = 0;

#define ANIMATION_TIME		0.01f
#define ANIMATION_STEP		5

void keyboardCallback(KeyCode code, KeyState state)
{
	if (code == KeyCode::KEY_UP_ARROW) {			// UP
		dy += (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}
	else if (code == KeyCode::KEY_DOWN_ARROW) {		// DOWN
		dy -= (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}
	else if (code == KeyCode::KEY_RIGHT_ARROW) {		// RIGHT
		dx += (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}
	else if (code == KeyCode::KEY_LEFT_ARROW) {		// LEFT
		dx -= (state == KeyState::KEY_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}

}

//가드 계속 움직이기 1번 게임
bool leftfin = false;

TimerID game_move_guard(ObjectID guard1) {

	if (guard1x >= 100 && guard1x <= 1000) {
		if (guard1x == 100) leftfin = true;
		else if (guard1x == 1000) leftfin = false;

		if (leftfin) {
			guard1x = guard1x + 5;
			showObject(guard1);
			hideObject(guard2);
		}
		else {
			guard1x = guard1x - 5;
			showObject(guard2);
			hideObject(guard1);
		}
		locateObject(guard1, scene, guard1x, 500);
		locateObject(guard2, scene, guard1x, 500);


		TimerID timername = createTimer(0.01f);
//		showTimer(timername);
		startTimer(timername);
		return timername;
	}
	else {

	}

}

bool trap1show = false;
//trap1번의 깜박임 trap1show가 true 일때 그 좌표에 가면 리셋하기 
TimerID game_trap(ObjectID trap1) {

	if (trap1show == true) {
		hideObject(trap2); hideObject(trap1);	showObject(trap3);  showObject(trap4); trap1show = false;
	}
	else {
		hideObject(trap4);  hideObject(trap3); showObject(trap2); showObject(trap1); trap1show = true;
	}

		TimerID timername1 = createTimer(0.7f);
		//showTimer(timername1);
		startTimer(timername1);
		return timername1;


}

bool case1 = false;
bool case2 = false;
bool power = true;

void room3_check() {

	if (case1 == false && case2 == false) {
		if (click3y == 0) {
			locateObject(ball3, scene3, 620, 0);
			showObject(up);
			hideObject(rights);
			hideObject(lefts);
			hideObject(down);
		} 
		else if (click3y > 0 && click3y < 6) {
			showObject(down);
			hideObject(lefts);

		}
		else if (click3y == 6) {
			case1 = false;
			case2 = false;
			showObject(lefts);
			showObject(up);
			showObject(down);
			hideObject(rights);


			if (click3x == -1) {
				case1 = true;
				hideObject(up);
				hideObject(down);
				showObject(rights);

			}
		}
		else if (click3y == 7) {
			case2 = true;
			hideObject(lefts);

		}
	}
	else if (case1 == true) {
		if (click3x == 0 && click3y == 6) {
			showObject(lefts);
			showObject(up);
			showObject(down);
			hideObject(rights); 
			case1 = false;

		}
		else if (click3y == 6) {
			if (click3x < 0 && click3x > -10) {
				showObject(lefts);
				showObject(rights);
				hideObject(up);
				hideObject(down);
			}
			else if (click3x == -10) {
				showObject(up);
				showObject(rights);
				hideObject(down);
				hideObject(lefts);
			}
		}

		else if (click3x == -10) {
			showObject(up);
			showObject(rights);
			hideObject(down);
			hideObject(lefts);
			if (click3y > 6 && click3y < 12) {
				showObject(up);
				showObject(down);
				hideObject(lefts);
				hideObject(rights);
			}
 			else if (click3y == 12) {
				showObject(rights);
				showObject(down);
				hideObject(lefts);
				hideObject(up);
			}
		}
		else if (click3y == 12) {
			if (click3x > -10 && click3x < -3) {
				showObject(rights);
				showObject(lefts);
				hideObject(down);
				hideObject(up);
			}
			else if (click3x == -3) {
				showObject(down);
				showObject(lefts);
				hideObject(rights);
				hideObject(up);
			}
		}
		else if (click3x == -3 && click3y == 11) {
			showObject(up);
			hideObject(lefts);
			hideObject(rights);
			hideObject(down);
		}
		}
	else if (case2 == true) {
		if (click3x == 0 && click3y == 6) {
			showObject(lefts);
			showObject(up);
			showObject(down);
			hideObject(rights);
			case2 = false;

		}
		else if (click3x == 0) {
			if (click3y > 6 && click3y < 9) {
				hideObject(lefts);
				showObject(up);
				showObject(down);
				hideObject(rights);
			}
			else if (click3y == 9) {
				showObject(rights);
				showObject(down);
				hideObject(lefts);
				hideObject(up);

			}
		}
		else if (click3y == 9) {
			if ((click3x > 0 && click3x < 9) ||(click3x>9&&click3x<11)) {
				showObject(lefts);
				showObject(rights);
				hideObject(down);
				hideObject(up);
			}
			else if (click3x == 9) {
				showObject(lefts);
				showObject(rights);
				showObject(down);
				hideObject(up);
			}
			else if (click3x == 11) {
				showObject(up);
				showObject(lefts);
				hideObject(down);
				hideObject(rights);
			}
		}
		else if (click3x == 9) {
			if (click3y < 9 && click3y>5) {
				showObject(up);
				showObject(down);
				hideObject(lefts);
				hideObject(rights);
			}
			else if (click3y == 5) {
				showObject(up);
				showObject(rights);
				hideObject(down);
				hideObject(lefts);
			}
		}
		else if (click3y == 5) {
			if (click3x == 10) {
				showObject(lefts);
				hideObject(rights);
				hideObject(down);
				hideObject(up);
			}
		}
		else if (click3x == 11) {
			if (click3y < 14 && click3y> 9) {
				showObject(up);
				showObject(down);
				hideObject(lefts);
				hideObject(rights);
			}
			else if (click3y == 14) {
				enterScene(endpage);
				showMessage("안전하게 깨끗한 숲으로 도착했습니다!");
			}
		}
	}


}

void room2_check() {
	
	if (x2 > 170 && x2 < 330 && (y2 < 230 && y2>70)) {
	//showMessage("도착");
	enterScene(scene3);
	x3 = 620; y3 = 0;
	locateObject(ball3, scene3, x3, y3);
	showMessage("이제 거의 다왔어요\n 제한시 올바른 길을 따라 하수구 밖으로 향하세요! ");

	timer3 = createTimer(timer3);
	showTimer(timer3);
	setTimer(timer3, 30.0f);
	startTimer(timer3);
	stopTimer(timer2);
	}
	else if (trap1show == false) {
		if (y2 < 300 && y2>50 && ((x2 > 430 && x2 < 600) || (x2 > 900 && x2 < 1100))) {
			x2 = 1200; y2 = 600;
			locateObject(ball2, scene2, x2, y2);
		}
	}
	else if (trap1show == true) {
		if (y2 < 450 && y2> 250 && ((x2 > 150 && x2 < 400) || (x2 > 650 && x2 < 850))) {
			x2 = 1200; y2 = 600;
			locateObject(ball2, scene2, x2, y2);
		}
	}

}

//룸 1 장애물들
void room1_check() {
	//철장과 충돌
	if (y > 300 - 50 && y < 300 + 84 + 50 && (x < 986 || x> 1140))
	{
		x = 1100; y = 0; locateObject(ball, scene, x, y);
	}
	//가드와 충돌
	else if (y > 450 && y < 550 && (x > guard1x - 50 && guard1x + 50 > x)) {
		x = 1100; y = 0; locateObject(ball, scene, x, y);

	}
	else if (y > 600 && (x > 450 && x < 800)) {
		enterScene(scene2);
		showMessage("아직은 너무 답답해요\n 곳곳에 숨겨져 있는 바퀴 벌레 약을 피해 하수구로 향하세요");

		x2 = 1200; y2 = 600;
		locateObject(ball2, scene2, x2, y2);
		timer2 = createTimer(ANIMATION_TIME);
		startTimer(timer2);
		x = 0; y = 0;
		stopTimer(timer1);

	}

}

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (object == start) {
		enterScene(scene); 
		showMessage("이곳은 너무 위험해요\n 바퀴벌레용 그물과 로봇청소기를 피해 쥐구멍으로 향하세요");
	}

	else if (object == gameexit) {
		power = !power;			// power를 toggle 한다.

		if (power == true) {
			// power가 true(불이 켜진 상태)이면, 조명을 높인다.
			setSceneLight(scene, 1.f);

			// 불이 켜지면 암호가 보이지 않는다.
			//showObject(stage1);
			showObject(gameexit);
			hideObject(restart);
			hideObject(reend);
		}
		else {
			// power가 false(불이 꺼진 상태)이면, 조명을 낮춘다.
			setSceneLight(scene, 0.2f);
			hideObject(gameexit);
			showObject(restart);
			showObject(reend);
		}
	}
	else if (object == gameexit2) {
		power = !power;			// power를 toggle 한다.

		if (power == true) {
			// power가 true(불이 켜진 상태)이면, 조명을 높인다.
			setSceneLight(scene2, 1.f);

			// 불이 켜지면 암호가 보이지 않는다.
			//showObject(stage1);
			showObject(gameexit2);
			hideObject(restart2);
			hideObject(reend2);
		}
		else {
			// power가 false(불이 꺼진 상태)이면, 조명을 낮춘다.
			setSceneLight(scene2, 0.2f);
			hideObject(gameexit2);
			showObject(restart2);
			showObject(reend2);
		}
	}
	else if (object == gameexit3) {
		power = !power;			// power를 toggle 한다.

		if (power == true) {
			// power가 true(불이 켜진 상태)이면, 조명을 높인다.
			setSceneLight(scene3, 1.f);

			// 불이 켜지면 암호가 보이지 않는다.
			//showObject(stage1);
			showObject(gameexit3);
			hideObject(restart3);
			hideObject(reend3);
		}
		else {
			// power가 false(불이 꺼진 상태)이면, 조명을 낮춘다.
			setSceneLight(scene3, 0.2f);
			hideObject(gameexit3);
			showObject(restart3);
			showObject(reend3);
		}
	}
	//power버튼이랑 순서 바꾸면 없어도 되는지 확인해봐야됨
	else if (object == restart) {
		setSceneLight(scene, 1.f);
		power = true;
		showObject(gameexit);
		hideObject(restart);
		hideObject(reend);
	}
	else if (object == reend) {
		endGame();
	}
	else if (object == restart2) {
		setSceneLight(scene2, 1.f);
		power = true;
		showObject(gameexit2);
		hideObject(restart2);
		hideObject(reend2);
	}
	else if (object == reend2) {
		endGame();
	}
	else if (object == restart3) {
		setSceneLight(scene3, 1.f);
		power = true;
		showObject(gameexit3);
		hideObject(restart3);
		hideObject(reend3);
	}
	else if (object == reend3) {
		endGame();
	}
	else if (object == up) {
		y3 += 50;
		click3y += 1;
		showObject(ball3);
		hideObject(ball3r);
		hideObject(ball3l);
		hideObject(ball3d);

		locateObject(ball3,scene3, x3, y3);
		room3_check();
	}
	else if (object == down) {
		y3 -= 50;
		click3y -= 1;
		showObject(ball3d);
		hideObject(ball3r);
		hideObject(ball3l);
		hideObject(ball3);
		locateObject(ball3d, scene3, x3, y3);

		room3_check();

	}
	else if (object == rights) {
		click3x += 1;
		x3 += 50;
		showObject(ball3r);
		hideObject(ball3);
		hideObject(ball3l);
		hideObject(ball3d);
		locateObject(ball3r, scene3, x3, y3);

		room3_check();

	}
	else if (object == lefts) {	
		x3 -= 50;
		click3x -= 1;
		showObject(ball3l);
		hideObject(ball3r);
		hideObject(ball3);
		hideObject(ball3d);
		locateObject(ball3l, scene3, x3, y3);

		room3_check();

	} 
}

void timerCallback(TimerID timer)
{
	if (timer == timer1) {
		x += dx; y += dy;

		locateObject(ball, scene, x, y);
		room1_check();
		setTimer(timer, ANIMATION_TIME);
		startTimer(timer);
	}
	if (timer == timer2) {
		x2 += dx; y2 += dy;
		locateObject(ball2, scene2, x2, y2);
		setTimer(timer, ANIMATION_TIME);
		startTimer(timer);
		room2_check();
	}
	if (timer == timer3) {
		click3x = 0;
		click3y = 0;
		case1 = false;
		case2 = false;
		x3 = 620; y3 = 0;
		locateObject(ball3, scene3, 620, 0);
		room3_check();
		setTimer(timer3,30.0f);
		startTimer(timer3);
		

	}
	if (timer == guardtimer) {
		guardtimer = game_move_guard(guard1);
	}
	if (timer == traptimer) {
		traptimer = game_trap(trap1);

	}

}

int main() 
{

//	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
//	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	setKeyboardCallback(keyboardCallback);

	scene = createScene("내부-위험한 집", "images/problem1.png");
	startpage = createScene("시작페이지", "images/시작화면.png");
	start = createObject("images/start.png", startpage, 600, 200, true);
//	timerbox = createObject("images/guard1.png", scene3, 600, 1100, true);

	gameexit = createObject("images/exit.png", scene, 30, 600, true);
	scaleObject(gameexit, 0.1f);
	restart= createObject("images/restart.png", scene, 600, 150, false);
	reend = createObject("images/end.png", scene, 600, 100, false);

	ball = createObject("images/바퀴벌레r.png");
	locateObject(ball, scene, x, y);
	showObject(ball);

	//게임1 
	fence = createObject("images/fence1r.png", scene, 0, 300, true);
	fence2 = createObject("images/fence2r.png", scene, 1100, 300, true);
	guard1 = createObject("images/로봇청소기.png", scene, 1100, 500, true);
	guard2 = createObject("images/로봇청소기2.png", scene, 1100, 500, true);
	
	door = createObject("images/door.png", scene, 500, 700, true);

	scene2 = createScene("외부-시멘트 마당", "images/problem2.png");
	scene3 = createScene("외부-하수구", "images/miro.png");
	endpage = createScene("외부-안전한 숲", "images/엔딩장면.jpg");

	gameexit2 = createObject("images/exit.png", scene2, 30, 600, true);
	scaleObject(gameexit2, 0.1f);
	restart2 = createObject("images/restart.png", scene2, 600, 150, false);
	reend2 = createObject("images/end.png", scene2, 600, 100, false);
	gameexit3 = createObject("images/exit.png", scene3, 30, 600, true);
	scaleObject(gameexit3, 0.1f);
	restart3 = createObject("images/restart.png", scene3, 600, 150, false);
	reend3 = createObject("images/end.png", scene3, 600, 100, false);

	starts3 = createObject("images/맨홀.png", scene2, 200, 100, true);
	scaleObject(starts3, 2.0f);

	ball2 = createObject("images/바퀴벌레왼.png", scene2, 1200, 600, true);
	trap1 = createObject("images/trap.png", scene2, 200, 300, true);
	scaleObject(trap1,2.0f);
	trap2 = createObject("images/trap.png", scene2, 700, 300, true);
	scaleObject(trap2, 2.0f);
	trap3 = createObject("images/trap.png", scene2, 450, 100, true);
	scaleObject(trap3, 2.0f);
	trap4 = createObject("images/trap.png", scene2, 950, 100, true);
	scaleObject(trap4, 2.0f);

	ball3 = createObject("images/바퀴벌레r.png ", scene3, 620, 0, true);
	ball3r = createObject("images/바퀴벌레오.png", scene3, 620, 0, false);
	ball3l = createObject("images/바퀴벌레왼.png", scene3, 620, 0, false);
	ball3d = createObject("images/바퀴벌레아.png", scene3, 620, 0, false);

	up = createObject("images/play-up.png", scene3, 500+300, 100+30, true);
	down = createObject("images/play-under.png", scene3, 500+300, 0+40, true);
	rights = createObject("images/play-right.png", scene3, 550+300, 35+50, true);
	lefts = createObject("images/play-left.png", scene3, 450+300, 35+50, true);
	room3_check();

	guardtimer = game_move_guard(guard1);
	traptimer = game_trap(trap1);

	showMessage("위험한 집에서 벗어나 깨끗한 숲으로 가기 위한 바퀴 벌레의 모험");

	timer1 = createTimer(ANIMATION_TIME);
	startTimer(timer1);

	startGame(startpage);

}