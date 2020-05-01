#include 'common.as'

enum Actions
{
	UP = 87,	//W
	DOWN = 83,	//S
	LEFT = 65,	//A
	RIGHT = 68,	//D
}

class CPlayer : IController
{
	ScriptableObject@ self;
	Transform@ transform;

	int isFacing = 1;
	float playerMoveSpeed = 5;

	CPlayer(ScriptableObject@ object)
	{
		@self = object;
	}

	void onUpdate()
	{
		@transform = FindTransform(self.getOwner());
		
		if (IsKeyDown(RIGHT))
		{
			transform.position.x += playerMoveSpeed * deltatime;			
		}
		else if (IsKeyDown(LEFT))
		{
			transform.position.x -= playerMoveSpeed * deltatime;
		}
		else if (IsKeyDown(UP))
		{
			transform.position.y += playerMoveSpeed * deltatime;
		}
		else if (IsKeyDown(DOWN))
		{
			transform.position.y -= playerMoveSpeed * deltatime;
		}

	}

	void onMessage(ref @message, const ScriptableObject @sender)
	{
		CMessage@ msg = cast<CMessage>(message);
		
		if( msg !is null)
		{
			if(msg.txt == 'ATK')
			{
				LoadSprite(self.getOwner(), "player-dead.png");
				self.kill();
			}
			if(msg.txt == 'COLLECT')
			{
				level_score = level_score + 1;
			}
		} 
	}
}