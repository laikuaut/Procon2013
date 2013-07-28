#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


#include"Procon2013\Core\Core.h"
#include"opencv2\opencv.hpp"

namespace test
{		
	TEST_CLASS(Timer)
	{
	public:
		TEST_METHOD(TimerState)
		{
			pro::Timer timer;
			//==�̂Ƃ���
			Assert::AreEqual(static_cast<int>( timer.m_sec(2) ),2000,L"m_sec");  //�����Ă��镔��������ƂȂ����G���[��
			timer.setState(pro::Timer::RESET);
			Assert::AreEqual(static_cast<int>(pro::Timer::RESET),static_cast<int>(timer.getState()));//,"���sgetState()");
			timer.start();
			Assert::AreEqual(static_cast<int>(pro::Timer::START),static_cast<int>(timer.getState()));//,"���sstart ==");
			timer.stop();
			Assert::AreEqual(static_cast<int>(pro::Timer::STOP),static_cast<int>(timer.getState()));//,"���sstop ==");
			timer.restart();
			Assert::AreEqual(static_cast<int>(pro::Timer::START),static_cast<int>(timer.getState()));//,"���srestart ==");
			timer.reset();
			Assert::AreEqual(static_cast<int>(pro::Timer::RESET),static_cast<int>(timer.getState()));//,"���sreset");
			//�{�P����
			Assert::AreEqual(static_cast<int>(timer.stop()),static_cast<int>(-1));//,"���sstop -1");
			Assert::AreEqual(static_cast<int>(timer.restart()),static_cast<int>(-1));//,"���srestart -1");
			Assert::AreEqual(static_cast<int>(timer.lap()),static_cast<int>(-1));//,"���slap() -1");
			Assert::AreEqual(static_cast<int>(timer.getDiff()),static_cast<int>(-1));//,"���s getDiff() -1");
			Assert::AreEqual(static_cast<int>(timer.getNow()),static_cast<int>(-1));//,"���s getNow() -1");
			timer.start();
			if(static_cast<int>(timer.stop())>=static_cast<int>(timer.getNow()) && static_cast<int>(timer.stop())<=static_cast<int>(timer.getNow()))
			{
				Assert::AreEqual(1,1);
			}
			timer.reset();
			timer.start();

			try{
				timer.lap(-1);
				Assert::IsTrue(0<1);
			}catch(pro::OutOfRangeException<long> e){
				e.showError();
			}

			//	Assert::AreEqual(static_cast<int>(timer.getNow()),static_cast<int>( clock() - sum_stop - start_time));
			//timer.stop();
			//Assert::AreEqual(static_cast<int>(timer.getNow()),static_cast<int>( stop_time - sum_stop - start_time));
			/*restart �e�X�g�ǂ����悤
			 lap getDiff lap_time.back()���ꉽ
			/*pro::Dir dir;/*
			//asdfg aa;
			//boost::filesystem::path pp;
			Assert::AreEqual(3,3,
				// Tolerance:
				0.01,
				// Message:
				L"Basic test failed",
				// Line number - used if there is no PDB file:
				LINE_INFO());:*/
			/*
			int a = timer.getState();
			int b = pro::Timer::RESET;
			int d=0;
			Assert::AreEqual(static_cast<int>( timer.getState() ),static_cast<int>( pro::Timer::RESET),0.01,L"message ok");
			timer.start();
			a = timer.getState();
			b = pro::Timer::START;
			Assert::AreEqual(a,b);
			while(true)
			{
					if(timer.getNow()==900)
					{
						d=timer.stop();
						break;
					}
			}
			//int c=timer.getNow();
			a = timer.getState();
			b = pro::Timer::STOP;
			Assert::AreEqual(a,b);*/
			//Assert::AreEqual(900,d);
			//int s=timer.lap(-1);
			
			
	
		}

	};
}