#include <bangtal.h>
using namespace bangtal;

//함수를 이용하는 법
//bool door1_mouseCallback(ObjectPtr object, int x, int y, MouseAction action)
//{
//   endGame(); //게임 종료한다
//   return true;
//}

int main()
{
    //장면 생성하기
    auto scene1 = Scene::create("룸1", "Images/배경-1.png");
    auto scene2 = Scene::create("룸2", "Images/배경-2.png");

    //열쇠 생성하기
    auto key = Object::create("Images/열쇠.png", scene1, 600, 150);
    key->setScale(0.2f);

    key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        key->pick();
        return true;
        });

    //화분 생성하기(열쇠를 숨기기위해 열쇠생성후 화분을 생성해야함)
    auto flowerpot_moved = false;
    auto flowerpot = Object::create("Images/화분.png", scene1, 550, 150);
    flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        if (flowerpot_moved == false) {
            if (action == MouseAction::MOUSE_DRAG_LEFT) {
                flowerpot->locate(scene1, 450, 150);
                flowerpot_moved = true;
            }
            else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
                flowerpot->locate(scene1, 650, 150);
                flowerpot_moved = true;
            }
        }
        return true;
        });

    //문 생성하기
    auto door1 = Object::create("Images/문-오른쪽-닫힘.png", scene1, 800, 270);
    auto open1 = false;

    //문을 클릭하면 이동한다        
    //lambda funstion
    door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        if (open1 == true) {      //문이 열린 상태
            scene2->enter();

        }
        else if (key->isHanded()) {      //문이 닫힌 상태
            door1->setImage("Images/문-오른쪽-열림.png");
            open1 = true;
        }
        else {
            showMessage("열쇠가 필요합니다.");
        }
        return true;
        });

    auto door2 = Object::create("Images/문-왼쪽-열림.png", scene2, 320, 270);
    door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        scene1->enter();
        return true;
        });

    auto open3 = false, locked3 = true;
    auto door3 = Object::create("Images/문-오른쪽-닫힘.png", scene2, 910, 270);
    door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        if (locked3) {               //문이 잠긴 상태
            showMessage("문이 잠겨있다.");
        }
        else if (open3 == true) {      //문이 열린 상태
            endGame();
        }
        else {                     //문이 닫힌 상태
            door3->setImage("Images/문-오른쪽-열림.png");
            open3 = true;
        }

        return true;

        });

    door3->setOnKeypadCallback([&](ObjectPtr object)->bool {
        locked3 = false;
        showMessage("철커덕!");
        return true;

        });
    //키패드 생성하기
    auto keypad = Object::create("Images/키패드.png", scene2, 885, 420);
    keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        showKeypad("BANGTAL", door3);
        return true;
        });
    //암호 생성하기
    auto password = Object::create("Images/암호.png", scene2, 400, 100, false);


    //스위치 생성하기
    auto lighted = true;
    auto button = Object::create("Images/스위치.png", scene2, 880, 440);
    button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        if (lighted) {
            scene2->setLight(0.2f);
            password->show();
            lighted = false;

        }
        else {
            scene2->setLight(1.0f);
            password->hide();
            lighted = true;
        }


        return true;
        });



    //게임을 시작한다
    startGame(scene1);


    return 0;
}