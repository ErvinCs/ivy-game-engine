#include 'common.as'

class Patrol : IController
{
	ScriptableObject@ self;
	Transform@ transform;
	Collidable@ collidable;
	Collidable@ playerCollidable;
	weakref<ScriptableObject> playerRef;

	float moveSpeed = 4;
	int direction = 0;
	float waitTime = 0;
	float constWaitTime = 0.3;

	Patrol(ScriptableObject@ object)
	{
		@self = object;
	}

	void onUpdate()
	{
		@transform = FindTransform(self.getOwner());
		@collidable = FindCollidable(self.getOwner());
		ScriptableObject @player = playerRef;
		if(player is null)
		{
			@player = FindObjectByTag('Player');
			@playerRef = player;
		}
		if (not(player is null))
		{
			@playerCollidable = FindCollidable(player.getOwner());
		}

		if(direction == 0) {
			transform.position.x += moveSpeed * deltatime;
			if (waitTime <= 0)
				if (IsColliding(self.getOwner()))
				{
					waitTime = constWaitTime;
					direction = 2;
				}
		} else if (direction == 1) {
			transform.position.y += moveSpeed * deltatime;
			if (waitTime <= 0)
				if (IsColliding(self.getOwner()))
				{
					waitTime = constWaitTime;
					direction = 3;
				}
		} else if (direction == 2) {
			transform.position.x -= moveSpeed * deltatime;
			if (waitTime <= 0)	
				if (IsColliding(self.getOwner()))
				{
					waitTime = constWaitTime;
					direction = 1;
				}
		} else if (direction == 3) {
			transform.position.y -= moveSpeed * deltatime;
			if (waitTime <= 0)
				if (IsColliding(self.getOwner()))
				{
					waitTime = constWaitTime;
					direction =  0;
				}
		}

		if (not(player is null))
		{
			if (AreColliding(collidable, playerCollidable))
			{
				self.sendMessage(CMessage('ATK'), player);
			}
		}

	}
}