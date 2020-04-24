#include 'common.as'

class Patrol : IController
{
	ScriptableObject@ self;
	Transform@ transform;
	Collidable@ collidable;
	Collidable@ playerCollidable;
	weakref<ScriptableObject> playerRef;

	float moveSpeed = 5;
	float patrolTime = 3;
	float currTime = 0;
	bool direction = true;

	Patrol(ScriptableObject@ object)
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

		currTime += deltatime;

		if(direction) {
			transform.position.y += moveSpeed * deltatime;
		} else {
			transform.position.y -= moveSpeed * deltatime;
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