#include "DefaultTypes/aevent.h"
#include "Engine/System/system.h"


Asoka::Log::Page& System::logPage = Asoka::Log::page("System");

//----------------------------------------------------------------------------------------------------------------------------------

Data <QVector <AIdentifier*>>		ACore::identifiers						= new QVector <AIdentifier*>;
Data <QVector <identifier>>			ACore::arr_identifiers					= new QVector <identifier>;
Data <int>							ACore::fld_identifiers_reserve_size		= new int(10);
Data <QVector <AThread*>>			ACore::threads_system					= new QVector <AThread*> { new AThread("thread_gui") };
Data <QVector <AThread*>>			ACore::threads_custom					= new QVector <AThread*>;
const isize							ACore::threads_system_count				= std::thread::hardware_concurrency();

AEvent <Asoka::ClosingType>			ACore::closing;


void ACore::initialize()
{
	threads_system.lock();
	for (int i = 0; i < threads_system_count - 1; i++)
	{
        AThread* new_thread = new AThread("thread_system_" + Asoka::to_string(i));
		threads_system().push_back(new_thread);
	}
	threads_system.unlock();
}

void ACore::close(Asoka::ClosingType _type)
{
	closing.operator()(_type);
	ACore::threads_system.lock();
	for (auto _thread : ACore::threads_system())
	{
		_thread->~AThread();
	}
	ACore::threads_system.clear();
	ACore::threads_system.unlock();

	ACore::threads_custom.lock();
	for (auto _thread : ACore::threads_custom())
	{
		_thread->~AThread();
	}
	ACore::threads_custom.clear();
	ACore::threads_custom.unlock();

	ACore::identifiers.lock();
	for (auto _identifier : ACore::identifiers())
	{
		_identifier->~AIdentifier();
	}
	ACore::identifiers.clear();
	ACore::identifiers.unlock();
}
