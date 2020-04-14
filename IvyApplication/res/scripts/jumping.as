#include 'common.as'

class Jumping : IController
{
	ScriptableObject@ self;
	Transform@ transform;
	Collidable@ collidable;
	Collidable@ playerCollidable;
	weakref<ScriptableObject> playerRef;

	float moveSpeed = 5;
	float topMargin = -3;
	float botMargin = 2;
	float patrolPosition = 0;
	bool direction = true;

	Jumping(ScriptableObject@ object)
	{
		@self = object;
	}

	void onUpdate()
	{
		@transform = FindTransform(self.getOwner());
		ScriptableObject @player = playerRef;
		if(player is null)
		{
			@player = FindObjectByTag('Player');
			@playerRef = player;
		}
		@collidable = FindCollidable(self.getOwner());
		@playerCollidable = FindCollidable(player.getOwner());

		if(direction) {
			transform.position.y += moveSpeed * deltatime;
			patrolPosition += moveSpeed * deltatime;
		} else {
			transform.position.y -= moveSpeed * deltatime;
			patrolPosition -= moveSpeed * deltatime;
		}

		if(patrolPosition <= topMargin) {
			direction = true;
		} else if(patrolPosition >= botMargin) {
			direction = false;
		}

		if (AreColliding(collidable, playerCollidable))
		{
			self.kill();
		}
	}
}