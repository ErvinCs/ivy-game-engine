#include 'common.as'

class Star : IController
{
	ScriptableObject@ self;
	Transform@ transform;

	Star(ScriptableObject@ object)
	{
		@self = object;
	}

	void onUpdate()
	{
		@transform = FindTransform(self.getOwner());
	}

	void onMessage(ref @message, const ScriptableObject @sender)
	{
		CMessage@ msg = cast<CMessage>(message);
		
		if(msg !is null && msg.txt == 'COLLECT')
		{
			self.kill();
		}
	}
}