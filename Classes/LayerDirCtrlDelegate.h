#ifndef LAYERDIRCTRLDELEGATE_H
#define LAYERDIRCTRLDELEGATE_H


class LayerDirCtrlDelegate
{
public:
    virtual void RunLeft() = 0;
    virtual void RunRight() = 0;
    virtual void Stop() = 0;
};

#endif // LAYERDIRCTRLDELEGATE_H
