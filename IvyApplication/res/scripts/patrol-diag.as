#include 'common.as'

class Patrol : IController
{
	ScriptableObject@ self;
	Transform@ transform;
	weakref<ScriptableObject> playerRef;

	float moveSpeed = 4;
	int direction = 0;
	float constWaitTime = 0.3;
	float waitTime = 0;

	Patrol(ScriptableObject@ object)
	{
		@self = object;
	}

	void onUpdate()
	{
		@transform = FindTransform(self.getOwner());
		ScriptableObject @player = playerRef;
		@player = FindObjectByTag('Player');
		@playerRef = player;

		if(direction == 0) {
			transform.position.x += moveSpeed * deltatime;
			transform.position.y += moveSpeed * deltatime;
			if (waitTime <= 0)
				if (IsColliding(self.getOwner()))
				{
					waitTime = constWaitTime;
					direction = 1;
				}
		} else if (direction == 1) {
			transform.position.x -= moveSpeed * deltatime;
			transform.position.y -= moveSpeed * deltatime;
			if (waitTime <= 0)
				if (IsColliding(self.getOwner()))
				{
					waitTime = constWaitTime;
					direction = 0;
				}
		} 

		waitTime -= deltatime;

		if (not(player is null))
		{
			if (AreColliding(self.getOwner(), player.getOwner()))
			{
				self.sendMessage(CMessage('ATK'), player);
			}
		}	
	}
}

	