#include "SceneBase.h"

USING_NS_CC;


Scene* SceneBase::createScene()
{
    CCLOGERROR("can not create base scene obj!!!!");
    return NULL;
}

bool SceneBase::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    regMsgHandler();

    return true;
}

// Print useful error message instead of segfaulting when files are not there.
void SceneBase::problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LoginScene.cpp\n");
}

