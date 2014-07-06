#include "AppDelegate.h"
#include "DiveInScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
   
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("DiveIn");
        director->setOpenGLView(glview);
    }
    
    director->setOpenGLView(glview);
    
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    
    Size frameSize = glview->getFrameSize();
    
    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.
    
    // if the frame's height is larger than the height of medium resource size, select large resource.
    if (frameSize.width > mediumResource.size.width)
    {
       //searchPath.push_back(largeResource.directory);
        director->setContentScaleFactor(largeResource.size.width/designResolutionSize.width);
    }
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.width > smallResource.size.width)
    {
        //searchPath.push_back(mediumResource.directory);
        director->setContentScaleFactor(mediumResource.size.width/designResolutionSize.width);
        //director->setContentScaleFactor(2.0f);
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
    else
    {
        //searchPath.push_back(smallResource.directory);
        director->setContentScaleFactor(smallResource.size.width/designResolutionSize.width);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    auto scene = DiveInScene::createScene();
    
    // initiate schedul. DiveInScene::run is main game loop.
    scene->schedule(schedule_selector(DiveInScene::run), 0);
    
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
