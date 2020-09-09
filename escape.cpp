#include<bangtal.h>
using namespace bangtal;

int main() {
	auto room1 = Scene::create("방1", "images/배경-2.png");

	auto room1_door1_opened = false; auto room1_door1_locked = true;
	auto room1_door1 = Object::create("images/문-왼쪽-닫힘.png", room1, 320, 270);
	auto room1_door2_opened = false; auto room1_door2_locked = true;
	auto room1_door2 = Object::create("images/문-오른쪽-닫힘.png", room1, 900, 270);
	auto room1_key1 = Object::create("images/열쇠.png", room1, 400, 200);
	room1_key1->setScale(0.3f);
	auto room1_keypad1 = Object::create("images/키패드.png", room1, 850, 400);
	room1_keypad1->setScale(4.0f);

	//방1 생성

	auto room2 = Scene::create("방2", "images/배경-1.png");
	auto room2_door1 = Object::create("images/문-왼쪽-열림.png", room2, 320, 300);
	auto room2_door2_opened = false; auto room2_door2_locked = true;
	auto room2_door2 = Object::create("images/문-오른쪽-닫힘.png", room2, 900, 250);
	auto room2_door3_opened = false; auto room2_door3_locked = true;
	auto room2_door3 = Object::create("images/문-오른쪽-닫힘.png", room2, 1100, 220);//최종 나가는 문
	auto room2_keypad1 = Object::create("images/키패드.png", room2, 850, 400);
	room2_keypad1->setScale(4.0f);
	auto room2_message1 = Object::create("images/암호.png", room2, 400, 100, false);
	auto room2_button = Object::create("images/스위치.png", room2, 450, 600);
	room2_button->setScale(3.0f);
	auto room2_light = true;
	//방2 생성

	auto room3 = Scene::create("방3", "images/배경-2.png");
	auto room3_door1 = Object::create("images/문-왼쪽-열림.png", room3, 320, 270);
	auto room3_key1 = Object::create("images/열쇠2.png", room3, 550, 160);
	room3_key1->setScale(0.3f);
	auto room3_plant1 = Object::create("images/화분.png", room3, 500, 150);
	room3_plant1->setScale(1.5f);
	auto room3_plant1_moved = false;
	//방3 생성


	auto room4 = Scene::create("방4", "images/배경-3.png");
	auto room4_door1 = Object::create("images/문-오른쪽-열림.png", room4, 900, 270);
	//방4 생성

	room1_key1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		room1_key1->pick();

		return true;

	});

	room1_door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (room1_door1_opened == true) {
			room4->enter();
		}
		else if (room1_key1->isHanded()) {
			room1_door1->setImage("images/문-왼쪽-열림.png");
			room1_door1_opened = true;
		}


		else { showMessage("열쇠가 필요하다."); }


		return true;
	});

	room1_door2->setOnKeypadCallback([&](ObjectPtr object)->bool {
		room1_door2_locked = false;
		showMessage("철컥- 문이 열리는 소리가 들렸다");

		return true;
	});

	room1_keypad1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("SECRET", room1_door2);

		return true;
	});

	room1_door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (room1_door2_locked) {
			showMessage("문이 잠겨있다. 비밀번호를 찾아야 할 것 같다.");

		}

		else if (room1_door2_opened == true) {
			room2->enter();
		}
		else {
			room1_door2->setImage("images/문-오른쪽-열림.png");
			room1_door2_opened = true;

		}


		return true;

	});
	//방1 동작

	room2_door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		room1->enter();
		return true;
	});

	room2_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (room2_light == true) {
			room2->setLight(0.3f);
			room2_light = false;
			room2_message1->show();
		}
		else
		{
			room2->setLight(1);
			room2_light = true;
			room2_message1->hide();
		}

		return true;
	});

	room2_door2->setOnKeypadCallback([&](ObjectPtr object)->bool {
		room2_door2_locked = false;
		showMessage("철컥- 문이 열리는 소리가 들렸다");

		return true;
	});

	room2_keypad1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("BANGTAL", room2_door2);

		return true;
	});

	room2_door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (room2_door2_locked) {
			showMessage("문이 잠겨있다. 비밀번호를 찾아야 할 것 같다.");

		}

		else if (room2_door2_opened == true) {
			room3->enter();
		}
		else {
			room2_door2->setImage("images/문-오른쪽-열림.png");
			room2_door2_opened = true;

		}


		return true;

	});

	room2_door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (room2_door3_opened == true) {
			endGame();
		}
		else if (room3_key1->isHanded()) {
			room2_door3->setImage("images/문-오른쪽-열림.png");
			room2_door3_opened = true;
		}


		else { showMessage("열쇠가 필요하다."); }


		return true;
	});

	room2_door3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		room2_door3_locked = false;
		showMessage("철컥- 문이 열리는 소리가 들렸다");

		return true;
	});

	//방2 동작
	room3_key1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		room3_key1->pick();

		return true;

	});

	room3_plant1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (room3_plant1_moved == false)
		{
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				room3_plant1->locate(room3, 350, 150);
				room3_plant1_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_UP) {
				room3_plant1->locate(room3, 500, 300);
				room3_plant1_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				room3_plant1->locate(room3, 650, 150);
				room3_plant1_moved = true;
			}

		}

		return true;
	});

	room3_door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		room2->enter();
		return true;
	});
	//방3 동작

	room4_door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		room1->enter();
		return true;
	});
	//방4 동작




	startGame(room1);
}