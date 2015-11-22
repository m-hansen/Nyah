class BulletC : public ObjectC
{
public:
	BulletC(float_t initPosX, float_t initPosY, float_t initVelX, float_t initVelY, int id);
	~BulletC();
	void update(DWORD milliseconds);
	virtual void render();
	void doCollisions();
	void move();
private:

	bool mEnabled;
	float mRadius;
	bool mAtRest;
};