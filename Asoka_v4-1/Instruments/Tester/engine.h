#pragma once
#include "../../asoka_engine.h"

using namespace Asoka;


namespace Tester
{
    namespace Engine
    {
        void Object()
        {
            output(L"\n\n���� 'asoka_object.h' �������� ���������� �������� ������ ��������, � ����� ����� � ���������� ����������� ���������� ��������:", Output_Textual);
            output(L"\n�������� ����� AMethod:", Output_Textual);
            astring wstr = L"test_string";
            wchar_t wchar[] = L"another_test_string";
            output(L"\n������ ������ wstring str: " + wstr, Output_Textual);
            AMethod <wstring, size_t, wchar_t*, size_t, size_t> method(&wstr, &wstring::copy);
            output(L"\n������ ������ wchar_t arr[]: " + astring(wchar), Output_Textual);
            output(L"\n�������� ����� wstring::copy(arr, 5, 5) ����������� ������ AMethod: ", Output_Textual);
            int size = method.run(wchar, 5, 5);
            output(L"\n�������� �������: " + astring(wchar) + L"\n������� �������: " + Asoka::to_string(size), Output_Textual);
            output(L"\n������������ �������� AMethod::object(): " + CLASS_NAME(method.object()), Output_Textual);
            output(L"\n������������ �������� AMethod::to_function(): " + CLASS_NAME(method.to_function()), Output_Textual);
            output(L"\n�������� ����� AFunction:", Output_Textual);
            AFunction <void, int> function_1(wait);
            output(L"\n�������� ������� Asoka::wait(2000) ����������� ������ AFunction:", Output_Textual);
            function_1.run(2000);
            output(L"\n������������ �������� AFunction::to_function(): " + CLASS_NAME(function_1.to_function()), Output_Textual);
        }

        void Time()
        {
            output(L"\n\n���� 'asoka_time.h' �������� ���������� ������� �������, ���� � ��������� �����:", Output_Textual);
            output(L"\n�������� ����� ATime:", Output_Textual);
            ATime time = ATime::currentTime();
            output(L"\n������� �����: " + time.to_astring(), Output_Textual);
            output(L"\n������� �����: (hh_mm): " + time.to_astring(HH_MM), Output_Textual);
        }

        void string()
        {
            output(L"\n\n���� 'asoka_string.h' �������� ���������� �����a ��� ������ �� ��������:", Output_Textual);
            output(L"\n�������� ����� AString:", Output_Textual);
            astring str = astring(L"test string ������� AbCdE_12345+-=%");
            output(L"\n���� ������: 'test string ������� AbCdE_12345+-=%'", Output_Textual);
            output(L"\n����� ������: '" + str + L"'", Output_Textual);
        }

        void Thread()
        {
            int tasks_count = Asoka::random(3, 6);
            AThread* athread = new AThread();
            AObject* obj = new AObject;
            AMethod <AObject, void, int> met(obj, &AObject::tester);
            Asoka::output(L"�������� ����� run(): ���������� ������� �� " + Asoka::to_string(tasks_count) + L" �����");
            for (int i = 0; i < tasks_count; i++)
            {
                athread->run(met, 5);
            }
            athread->waitForFinished();

            Asoka::output(L"�������� ����� addTask(): ���������� ������� �� " + Asoka::to_string(tasks_count) + L" �����");
            for (int i = 0; i < tasks_count; i++)
            {
                athread->addTask(met, 5);
            }
            athread->run();
            athread->waitForFinished();
        }

        void all()
        {
            output(L"\n\n������, ���� ����� �����. � - ������ ��� ���������� ������������������ ����������.");
            wait(2000);
            output(L"\n�� ��������� ������ ��� ������������ ������� ���������.");
            wait(2000);
            output(L"\n������� ������������:");
            wait(2000);

            Engine::string();
            Engine::Time();

            Engine::Object();
            Engine::Thread();

            output(L"\n\n����� ������������");
        }
    };
}