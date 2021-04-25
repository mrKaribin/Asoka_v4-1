#pragma once
#include "../../asoka_engine.h"

using namespace Asoka;


namespace Tester
{
    namespace Engine
    {
        void Object()
        {
            output(L"\n\nФайл 'asoka_object.h' содержит реализацию базового класса иерархии, а также типов и алгоритмов реализующих событийный механизм:", Output_Textual);
            output(L"\nТестирую класс AMethod:", Output_Textual);
            astring wstr = L"test_string";
            wchar_t wchar[] = L"another_test_string";
            output(L"\nСоздаю строку wstring str: " + wstr, Output_Textual);
            AMethod <wstring, size_t, wchar_t*, size_t, size_t> method(&wstr, &wstring::copy);
            output(L"\nСоздаю массив wchar_t arr[]: " + astring(wchar), Output_Textual);
            output(L"\nВыполняю метод wstring::copy(arr, 5, 5) посредством класса AMethod: ", Output_Textual);
            int size = method.run(wchar, 5, 5);
            output(L"\nЗначение массива: " + astring(wchar) + L"\nВозврат функции: " + Asoka::to_string(size), Output_Textual);
            output(L"\nВозвращаемое значение AMethod::object(): " + CLASS_NAME(method.object()), Output_Textual);
            output(L"\nВозвращаемое значение AMethod::to_function(): " + CLASS_NAME(method.to_function()), Output_Textual);
            output(L"\nТестирую класс AFunction:", Output_Textual);
            AFunction <void, int> function_1(wait);
            output(L"\nВыполняю функцию Asoka::wait(2000) посредством класса AFunction:", Output_Textual);
            function_1.run(2000);
            output(L"\nВозвращаемое значение AFunction::to_function(): " + CLASS_NAME(function_1.to_function()), Output_Textual);
        }

        void Time()
        {
            output(L"\n\nФайл 'asoka_time.h' содержит реализацию классов времени, даты и временной точки:", Output_Textual);
            output(L"\nТестирую класс ATime:", Output_Textual);
            ATime time = ATime::currentTime();
            output(L"\nТекущее время: " + time.to_astring(), Output_Textual);
            output(L"\nТекущее время: (hh_mm): " + time.to_astring(HH_MM), Output_Textual);
        }

        void string()
        {
            output(L"\n\nФайл 'asoka_string.h' содержит реализацию классa для работы со строками:", Output_Textual);
            output(L"\nТестирую класс AString:", Output_Textual);
            astring str = astring(L"test string русский AbCdE_12345+-=%");
            output(L"\nВвод данных: 'test string русский AbCdE_12345+-=%'", Output_Textual);
            output(L"\nВывод данных: '" + str + L"'", Output_Textual);
        }

        void Thread()
        {
            int tasks_count = Asoka::random(3, 6);
            AThread* athread = new AThread();
            AObject* obj = new AObject;
            AMethod <AObject, void, int> met(obj, &AObject::tester);
            Asoka::output(L"Тестирую метод run(): выстраиваю очередь из " + Asoka::to_string(tasks_count) + L" задач");
            for (int i = 0; i < tasks_count; i++)
            {
                athread->run(met, 5);
            }
            athread->waitForFinished();

            Asoka::output(L"Тестирую метод addTask(): выстраиваю очередь из " + Asoka::to_string(tasks_count) + L" задач");
            for (int i = 0; i < tasks_count; i++)
            {
                athread->addTask(met, 5);
            }
            athread->run();
            athread->waitForFinished();
        }

        void all()
        {
            output(L"\n\nПривет, меня зовут Асока. Я - движок для разработки кроссплатформенных приложений.");
            wait(2000);
            output(L"\nВы запустили модуль для тестирования базовых библиотек.");
            wait(2000);
            output(L"\nНачинаю тестирование:");
            wait(2000);

            Engine::string();
            Engine::Time();

            Engine::Object();
            Engine::Thread();

            output(L"\n\nКонец тестирования");
        }
    };
}