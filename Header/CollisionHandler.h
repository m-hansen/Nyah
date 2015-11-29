class CollisionHandlerC
{
public:
	static CollisionHandlerC *CreateInstance();
	static CollisionHandlerC *GetInstance() { return sInstance; };
	bool CollisionOccuredRect(CollisionRectangle* rectA, CollisionRectangle* rectB);
private:
	static CollisionHandlerC *sInstance;
};
