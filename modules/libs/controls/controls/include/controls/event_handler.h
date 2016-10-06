#ifndef PROJECT_EVENT_HANDLER_H
#define PROJECT_EVENT_HANDLER_H


class EventHandler {
public:
    virtual ~EventHandler(){}

    virtual void HandleEvents() = 0;

private:
};


#endif //PROJECT_EVENT_HANDLER_H
