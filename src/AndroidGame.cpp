//
// Created by dar on 1/23/16.
//

#include "AndroidGame.h"
#include "core/Core.h"
#include "render/Renderer.h"
#include "core/map/TiledTxtMapLoader.h"
#include "logging.h"

AndroidGame::AndroidGame() {
    this->timer = new Timer();

    MapLoader *mapLoader = new TiledTxtMapLoader("test_map.txt");
    Map *bmap = mapLoader->loadMap();

    this->core = new Core(bmap);
    this->renderer = new Renderer(core);
    this->renderer->init();
}

void AndroidGame::run() {
    this->update(); //TODO No delta time for now
    this->renderer->run();
}

void AndroidGame::update() {
    this->core->getMap()->update();
    this->core->getMap()->getWorld()->Step(TIME_STEP, 8, 3);
    for (int i = 0; i < this->core->getMap()->getEntities().size(); i++) {
        Entity *entity = this->core->getMap()->getEntities().at(i);
        if (entity->isToBeDeleted()) {
            this->core->getMap()->removeEntity(entity);
            i--;

        }
    }
    double dx = (this->core->getPlayer()->getX() + this->core->getPlayer()->getWidth() / 2 - 1) * this->core->getBlockSize() * this->core->getGeneralScale() + this->core->getCamX();
    double dy = (this->core->getPlayer()->getY() + this->core->getPlayer()->getHeight() / 2 - 1) * this->core->getBlockSize() * this->core->getGeneralScale() + this->core->getCamY();
    if (abs(dx) > 2) this->core->setCamX(-this->core->getCamX() + (dx) * 0.05);
    if (abs(dy) > 2) this->core->setCamY(-this->core->getCamY() + (dy) * 0.05);
}

void AndroidGame::resize(int width, int height) {
    this->renderer->resize((unsigned int) width, (unsigned int) height);
}

void AndroidGame::handleTouch(int i, int action, float x, float y) {
    double playerSpeed = this->core->getPlayer()->getSpeed();
    this->core->getPlayer()->applyImpulse(playerSpeed, 0);
}

AndroidGame::~AndroidGame() {
    delete this->core;
}

AndroidGame *game;

/* It's here just to stop IDE from reformatting (and breaking) code below. */
#ifdef __ANDROID__

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_init(JNIEnv *env, jobject obj) {
    LOGD("C++ init");
    game =  new AndroidGame();
    jclass cls = env->GetObjectClass(obj);
    jmethodID mid = env->GetMethodID(cls, "loadTexture", "()V");
    if (mid == 0) {
        return;
    }
    env->CallVoidMethod(obj, mid);
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_resize(JNIEnv *env, jobject obj, jint width, jint height) {
    LOGD("C++ resize(%d, %d)", width, height);
    game->resize(width, height);
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_tick(JNIEnv *env, jobject obj) {
    game->run();
}

JNIEXPORT void JNICALL Java_tk_approach_android_spookytom_JniBridge_handleTouch(JNIEnv *env, jobject obj, jint i,  jint action, jfloat x, jfloat y) {
    LOGD("C++ touch. i:%d, action:%d, x:%f, y:%f", i, action, x, y);
    game->handleTouch(i, action, x, y);
}

#endif // __ANDROID__