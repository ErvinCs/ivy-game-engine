#include 'common.as'

class Patrol : IController
{
	ScriptableObject@ self;
	Transform@ transform;
	Collidable@ collidable;
	Collidable@ playerCollidable;
	weakref<ScriptableObject> playerRef;

	float moveSpeed = 3;
	int direction = 0;

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
			transform.position.y += moveSpeed * deltatime;
		} else if (direction == 1) {
			transform.position.x -= moveSpeed * deltatime;
			transform.position.y -= moveSpeed * deltatime;
		} 

		if (not(player is null))
		{
			if (AreColliding(collidable, playerCollidable))
			{
				self.sendMessage(CMessage('ATK'), player);
			}
		}

		if (IsColliding(self.getOwner()))
		{
			direction = (direction + 1) % 2;
		}
	}
}

	