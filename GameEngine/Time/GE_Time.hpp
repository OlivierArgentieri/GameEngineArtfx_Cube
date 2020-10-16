
class GE_Time
{
private:
	static double currentTime;
	static double oldTime;
	static float deltaTime;

public:
	GE_Time() = delete;
	GE_Time(GE_Time& const) = delete;
	
	static float GetDeltaTime();
	static void BeginFrame();
	static void EndFrame();

};