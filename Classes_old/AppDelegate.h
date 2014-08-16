#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;

static Resource smallResource = {cocos2d::Size(480, 320), "iPhone"};
static Resource mediumResource = {cocos2d::Size(1024,768), "iPad"};
static Resource largeResource = {cocos2d::Size(2048, 1536), "iPadHD"};
static cocos2d::Size designResolutionSize = cocos2d::Size(2048, 1536);

//auto fileUtils = cocos2d::FileUtils::getInstance;
//std::vector<std::string> searchPath;

class  AppDelegate : private cocos2d::Application
{
public:
    
    AppDelegate();
    virtual ~AppDelegate();
    
    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

