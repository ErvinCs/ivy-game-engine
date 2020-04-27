#include 'common.as'

enum Actions
{
	UP = 87,	//W
	DOWN = 83,	//S
	LEFT = 65,	//A
	RIGHT = 68,	//D
	THROW = 81	//Q
}

class CPlayer : IController
{
	ScriptableObject@ self;
	Transform@ transform;

	// 1-right, 2-left, 3-up, 4-down
	int isFacing = 1;
	int rageCount = 1;
	float playerMoveSpeed = 7;


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

		//if (Colliding with star)
		//{
		//	send message
		//  collect = collect + 1;
		//}
	}

	void onMessage(ref @message, const ScriptableObject @sender)
	{
		CMessage@ msg = cast<CMessage>(message);
		
		if( msg !is null && msg.txt == 'ATK' && rageCount > 0)
		{
			self.kill();
		}
	}
}