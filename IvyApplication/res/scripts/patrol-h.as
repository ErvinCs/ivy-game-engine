#include 'common.as'

class Patrol : IController
{
	ScriptableObject@ self;
	Transform@ transform;
	Collidable@ collidable;
	Collidable@ playerCollidable;
	weakref<ScriptableObject> playerRef;

	float moveSpeed = 0;
	float patrolTime = 0;
	float currTime = 0;
	bool direction;

	Patrol(ScriptableObject@ object)
	{
		@self = object;
		direction = true;
		moveSpeed = 5;
		patrolTime = 3;
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

		currTime += deltatime;

		if(direction) {
			transform.position.x += moveSpeed * deltatime;
		} else {
			transform.position.x -= moveSpeed * deltatime;
		}

		if(currTime >= patrolTime) {
			currTime = 0;
			direction = not direction;
		} 

		
		if (AreColliding(collidable, playerCollidable))
		{
			self.sendMessage(CMessage('ATK'), player);
		}
	}
}