#include "PlayableCharacter.h"

mm::PlayableCharacter::PlayableCharacter() {
    // TODO: make it configurable
    sprite.load("content/characters/megaman/megaman.png", 32, 32, 0, 0, 0, 0, 5, 4);
    sprite.loadAnimation("content/characters/megaman/megaman-animation.xml");
    sprite.setAnimation("run");
    sprite.play();
    sprite.setMirror(true);
    position.x = 40;
    position.y = 20;
}

mm::PlayableCharacter::~PlayableCharacter() {
}

void mm::PlayableCharacter::HandleEvents(cgf::InputManager* inputManager) {
/*dirx = diry = 0;
    int newDir = currentDir;

    if(im->testEvent("left")) {
        dirx = -1;
        newDir = LEFT;
    }

    if(im->testEvent("right")) {
        dirx = 1;
        newDir = RIGHT;
    }

    if(im->testEvent("up")) {
        diry = -1;
        newDir = UP;
    }

    if(im->testEvent("down")) {
        diry = 1;
        newDir = DOWN;
    }*/
}
