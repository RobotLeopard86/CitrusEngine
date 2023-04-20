#include "CitrusClient.h"
#include "Assert.h"
#include "IO/Window.h"
#include "Log.h"
#include "Utilities.h"

namespace CitrusEngine {

    //Required definitions of static members
    CitrusClient* CitrusClient::instance = nullptr;
    EventManager* CitrusClient::eventManager = nullptr;

    CitrusClient::CitrusClient(){
        //Confirm we are initializing the first client
        Asserts::EngineAssert(instance != nullptr, "Client instance already exists!");

        //Set singleton instance
        instance = this;

        //Allow the app to run
        run = true;

        //Set up event consumers
        wceConsumer = new EventConsumer(BIND_MEMBER_FUNC(CitrusClient::Shutdown));

        //Set up event manager
        eventManager = new EventManager();
        eventManager->SubscribeConsumer("WindowClose", wceConsumer);
    }

    //Base client does not need a destructor
    CitrusClient::~CitrusClient() {}

    void CitrusClient::Run(){
        //Create window
        Window::Create(id, 1280, 720);

        while(run){
            Window::Update();
        }

        //Prepare eventManager for freeing by unsubscribing all consumers;
        eventManager->Shutdown();

        Window::Destroy();
        
        //Free pointers
        delete eventManager;
        delete wceConsumer;
    }

    void CitrusClient::Shutdown(Event& e){
        e.handled = true;
        run = false;
    } 
}