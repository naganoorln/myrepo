#include <stdio.h>
// Define car DASHBOARD Events
typedef enum
{
    EVENT_LOW_FUEL, // Low fuel warning
    EVENT_ENGINE_OVERHET, // Engine overheating alert
    EVENT_SEATBELT, // Seatbelt remainder
    EVENT_DOAR_OPEN, // Doar open alert
    EVENT_CHECK_ENGINE, // Check engine warning
    EVENT_MAX // Total number of events
}EventType;

// Define the callback function type
typedef void (*EventCallback)(void);

// Array to store registered events
EventCallback eventHandlers[EVENT_MAX] = {NULL};

// Function to register an event handler
void registerEventHandler(EventType event, EventCallback callback)
{
    if(event < EVENT_MAX)
    {
        eventHandlers[event] = callback;
    }
}

// Function to trigger an event
void triggerEvent(EventType event)
{
    if(event < EVENT_MAX && eventHandlers[event])
    {
        eventHandlers[event](); // Call the registered function
    } else {
        printf("No handler registered for event %d\n", event);
    }
}

// Event handler functions
void onLowFuel()
{
    printf("[DASHBOARD] Warning: Low Fuel Please Refuel Soon.\n");
}
void onEngineOverheat()
{
    printf("[DASHBOARD] Critical Alert: Engine overheating! Stop Immediately.\n");
}
void onSeatBeltReminder()
{
    printf("[DASHBOARD] Reminder: Please wear your Seatbelt.\n");
}
void onDoarOpen()
{
    printf("[DASHBOARD] Warning: Doar Open! Please Close It.\n");
}
void OnCheckEngine()
{
    printf("[DASHBOARD] Alert: Check Engine! Visit a Service Center.\n");
}
int main()
{
   // Register all events
   registerEventHandler(EVENT_LOW_FUEL, onLowFuel);
   registerEventHandler(EVENT_ENGINE_OVERHET, onEngineOverheat);
   registerEventHandler(EVENT_SEATBELT, onSeatBeltReminder);
   registerEventHandler(EVENT_DOAR_OPEN, onDoarOpen);
   registerEventHandler(EVENT_CHECK_ENGINE, OnCheckEngine);
   
   //Trigger event handlers
   triggerEvent(EVENT_LOW_FUEL);
   triggerEvent(EVENT_ENGINE_OVERHET);
   triggerEvent(EVENT_SEATBELT);
   triggerEvent(EVENT_DOAR_OPEN);
   triggerEvent(EVENT_CHECK_ENGINE);
   triggerEvent(999); // Invalid event
   return 0;
}

