#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H
class MouseListener
{ /* data */
public:
    virtual void onMouseMove();
    virtual void onMouseClick();
    virtual void onMousePressed();
    virtual void onMouseReleased();
};

#endif;