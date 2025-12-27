#ifndef VISION_COMPONENT_INTERFACE_H
#define VISION_COMPONENT_INTERFACE_H



class IVisionComponent
{
public:
	virtual ~IVisionComponent() {}
	virtual Real getShroudClearingRange() const = 0;
	virtual Real getVisionRange() const = 0;
};

#endif // VISION_COMPONENT_INTERFACE_H
