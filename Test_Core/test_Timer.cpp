#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include"Procon2013\Core\Core.h"
#include<sstream>

namespace test
{		

	TEST_CLASS(Timer)
	{
	private:

		pro::Timer timer;

		// �X�e�[�^�X�̃e�X�g�Ɏg�p
		void checkState(const pro::Timer::t_state& expected,const wchar_t* message=NULL){
			Assert::AreEqual(static_cast<int>(expected)
							,static_cast<int>(timer.getState())
							,message,LINE_INFO());
		}

	public:

		TEST_CLASS_INITIALIZE(TimerInitialize){
			writeMessage("In Timer Initialize");
		}

		TEST_CLASS_CLEANUP(TimerCleanup){
			writeMessage("In Timer Cleanup");
		}

		//BEGIN_TEST_METHOD_ATTRIBUTE(�R���X�g���N�^�����l)
		//	TEST_PRIORITY(1)
		//END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD_INITIALIZE(TestInitialize){

		}

		TEST_METHOD_CLEANUP(TestCleanup){
			timer.reset();
		}

		TEST_METHOD(�R���X�g���N�^�����l){
			writeMessage("In �R���X�g���N�^�����l");

			pro::Timer timer;

			writeMessage("�R���X�g���N�^�ɂ�鏉���l",1);
			Assert::AreEqual(-1L,timer.getStartTime()
							,L"start_time != -1",LINE_INFO());
			Assert::AreEqual(-1L,timer.getStopTime()
							,L"stop_time != -1",LINE_INFO());
			Assert::AreEqual(0L,timer.getSumStop()
							,L"sum_stop != 0",LINE_INFO());

			writeMessage("�R���X�g���N�^�����̃X�e�[�^�X",1);
			checkState(pro::Timer::RESET,L"state != RESET");

			// ���b�v�p�ϐ��쐬
			vector<clock_t> lap;
			const type_info& info = typeid(lap);

			writeMessage("�^�`�F�b�N",1);
			Assert::IsTrue(info==typeid(timer.getLapTime())
							,L"�^��vector<clock_t>�ł���܂���",LINE_INFO());

			writeMessage("���b�v�������̊m�F",1);
			lap = timer.getLapTime();
			Assert::IsTrue(lap.empty()
							,L"lap����ł���܂���",LINE_INFO());
		
		}

		TEST_METHOD(�X�e�[�^�X�̒l���m�F){
			writeMessage("In �X�e�[�^�X�̒l���m�F");

			writeMessage("�W���I�ȗ���̃e�X�g",1);
			timer.start();
			checkState(pro::Timer::START,L"RESET->start()");
			timer.stop();
			checkState(pro::Timer::STOP,L"START->stop()");
			timer.restart();
			checkState(pro::Timer::START,L"STOP->restart()");
			timer.reset();
			checkState(pro::Timer::RESET,L"START->reset()");

			writeMessage("RESET��Ԃ���̑J��",1);
			timer.stop();
			checkState(pro::Timer::RESET,L"RESET->stop()");
			timer.restart();
			checkState(pro::Timer::RESET,L"RESET->restart()");
			timer.reset();
			checkState(pro::Timer::RESET,L"RESET->reset()");
			timer.start();
			checkState(pro::Timer::START,L"RESET->start()");

			writeMessage("START��Ԃ���̑J��",1);
			timer.start();
			checkState(pro::Timer::START,L"START->start()");
			timer.restart();
			checkState(pro::Timer::START,L"START->restart()");
			timer.reset();
			checkState(pro::Timer::RESET,L"START->reset()");

			writeMessage("STOP��Ԃ���̑J��",1);
			timer.start();
			timer.stop();
			timer.reset();
			checkState(pro::Timer::RESET,L"STOP->reset()");
			timer.start();
			timer.stop();
			timer.start();
			checkState(pro::Timer::START,L"STOP->start()");

		}

		TEST_METHOD(m_sec���\�b�h�e�X�g){
			writeMessage("In m_sec���\�b�h�e�X�g");
			
			string per_sec_str,clock_per_sec_str;

		#ifdef TEST_MESSAGE
			std::stringstream ss;
			ss << "pro::Timer::PER_SEC = " << pro::Timer::PER_SEC;
			per_sec_str = ss.str();
			ss.str("");
			ss.clear(std::stringstream::goodbit);
			ss << "CLOCKS_PER_SEC = " << CLOCKS_PER_SEC;
			clock_per_sec_str = ss.str();
		#endif

			writeMessage(per_sec_str,1);
			Assert::AreEqual(pro::Timer::PER_SEC,pro::Timer::m_sec(1)
							,L"pro::Timer::PER_SEC�ƈ�v���Ȃ�",LINE_INFO());
			
			writeMessage(clock_per_sec_str,1);
			Assert::AreEqual(static_cast<long>(CLOCKS_PER_SEC),pro::Timer::m_sec(1)
							,L"CLOCKS_PER_SEC�ƈ�v���Ȃ�",LINE_INFO());
		}

		TEST_METHOD(start���\�b�h�e�X�g){
			writeMessage("In start���\�b�h�e�X�g");
			
			long start_time;

			writeMessage("state�̊m�F�� �X�e�[�^�X�̒l���m�F() �����s���邱��",1);


			writeMessage("�W���I�ȗ����start_time�̒l�m�F",1);
			Assert::AreEqual(-1L,timer.getStartTime()
							,L"reset()->start_time",LINE_INFO());
			timer.start();
			start_time = timer.getStartTime();
			Assert::AreEqual(start_time,timer.getStartTime()
							,L"start()->start_time",LINE_INFO());
			timer.stop();
			Assert::AreEqual(start_time,timer.getStartTime()
							,L"stop()->start_time",LINE_INFO());
			timer.restart();
			Assert::AreEqual(start_time,timer.getStartTime()
							,L"restart()->start_time",LINE_INFO());
			timer.reset();
			Assert::AreEqual(-1L,timer.getStartTime()
							,L"reset()->start_time",LINE_INFO());


			writeMessage("2��ڂ�start()��1��ڂ�start()�̔�r",1);
			timer.start();
			while(start_time==clock());
			Assert::IsTrue(start_time < timer.getStartTime()
							,L"2��ڂ�start()�ƈ��ڂ�start()�̔�r",LINE_INFO());

		}

		TEST_METHOD(stop���\�b�h�e�X�g){
			writeMessage("In stop���\�b�h�e�X�g");

			writeMessage("state�̊m�F�� �X�e�[�^�X�̒l���m�F() �����s���邱��",1);

			long stop_time;

			writeMessage("�l�ω��̊m�F",1);
			Assert::AreEqual(-1L,timer.stop()
							,L"RESET->stop()",LINE_INFO());
			timer.start();
			Assert::AreEqual(-1L,timer.getStopTime()
							,L"RESET->START",LINE_INFO());
			Assert::AreNotEqual(-1L,timer.stop()
							,L"START->stop()",LINE_INFO());
			Assert::AreNotEqual(-1L,timer.getStopTime()
							,L"STOP",LINE_INFO());
			timer.restart();
			Assert::AreEqual(-1L,timer.getStopTime()
							,L"STOP->restart()",LINE_INFO());
			Assert::AreNotEqual(-1L,timer.stop()
							,L"START->stop()",LINE_INFO());
			Assert::AreNotEqual(-1L,timer.getStopTime()
							,L"STOP",LINE_INFO());
			timer.reset();
			Assert::AreEqual(-1L,timer.getStopTime()
							,L"START->reset()",LINE_INFO());
			Assert::AreEqual(-1L,timer.stop()
							,L"RESET->stop()",LINE_INFO());
			Assert::AreEqual(-1L,timer.getStopTime()
							,L"STOP",LINE_INFO());


			writeMessage("stop��2��A���g�p",1);
			timer.start();
			stop_time = timer.stop();
			Assert::AreEqual(-1L,timer.stop()
							,L"2��ژA����stop�̕Ԃ�l",LINE_INFO());
			Assert::AreEqual(stop_time,timer.getStopTime()
							,L"2��ژA����stop�ł�stop_time�̒l�͕ω����Ȃ�",LINE_INFO());

			
			writeMessage("stop��2��ڈȍ~�̎g�p",1);
			timer.restart();
			while(stop_time==clock());
			Assert::IsTrue(stop_time<timer.stop()
							,L"2��ڂ̎g�p��stop_time�̕ω��m�F(restart)",LINE_INFO());
			timer.start();
			Assert::IsTrue(stop_time<timer.stop()
							,L"2��ڂ̎g�p��stop_time�̕ω��m�F(start)",LINE_INFO());


		}

		TEST_METHOD(restart���\�b�h�e�X�g){
			writeMessage("In restart���\�b�h�e�X�g");

			writeMessage("state�̊m�F�� �X�e�[�^�X�̒l���m�F() �����s���邱��",1);

			long stop_time,sum_stop;


			writeMessage("�l�ω��̊m�F",1);
			Assert::AreEqual(-1L,timer.restart()
							,L"RESET->restart()",LINE_INFO());
			Assert::AreEqual(0L,timer.getSumStop()
							,L"RESET->restart()",LINE_INFO());
			timer.start();
			Assert::AreEqual(-1L,timer.restart()
							,L"START->restart()",LINE_INFO());
			Assert::AreEqual(0L,timer.getSumStop()
							,L"START->restart()",LINE_INFO());
			stop_time = timer.stop();
			while(stop_time==clock());
			Assert::AreNotEqual(-1L,timer.restart()
							,L"STOP->restart()",LINE_INFO());
			Assert::AreNotEqual(0L,timer.getSumStop()
							,L"STOP->restart()",LINE_INFO());

			
			writeMessage("2��ڈȍ~��sum_stop�����m�F",1);
			sum_stop = timer.getSumStop();
			stop_time = timer.stop();
			while(stop_time==clock());
			Assert::IsTrue(sum_stop<timer.restart()
							,L"STOP->restart()",LINE_INFO());
			Assert::IsTrue(sum_stop<timer.getSumStop()
							,L"STOP->restart()",LINE_INFO());

		}

		TEST_METHOD(reset���\�b�h�e�X�g){
			writeMessage("In reset���\�b�h�e�X�g");

			writeMessage("state�̊m�F�� �X�e�[�^�X�̒l���m�F() �����s���邱��",1);

			long stop_time;

			
			writeMessage("�l�ω��̊m�F(start,sum_stop,lap)",1);
			timer.start();
			stop_time = timer.stop();
			while(stop_time == clock());
			timer.restart();
			timer.lap();
			Assert::AreNotEqual(-1L,timer.getStartTime()
							,L"start_time�ω�",LINE_INFO());
			Assert::AreNotEqual(0L,timer.getSumStop()
							,L"sum_stop�ω�",LINE_INFO());
			Assert::IsFalse(timer.getLapTime().empty()
							,L"lap�ω�",LINE_INFO());

			
			writeMessage("rest�ɂ�鏉�����m�F",1);
			timer.reset();
			Assert::AreEqual(-1L,timer.getStartTime()
							,L"start_time������",LINE_INFO());
			Assert::AreEqual(0L,timer.getSumStop()
							,L"sum_stop������",LINE_INFO());
			Assert::IsTrue(timer.getLapTime().empty()
							,L"lap������",LINE_INFO());

			
			writeMessage("�l�ω��̊m�F(stop)",1);
			timer.start();
			timer.stop();
			Assert::AreNotEqual(-1L,timer.getStopTime()
							,L"stop_time�ω�",LINE_INFO());
			
			
			writeMessage("rest�ɂ�鏉�����m�F",1);
			timer.reset();
			Assert::AreEqual(-1L,timer.getStopTime()
							,L"stop_time������",LINE_INFO());


		}

		TEST_METHOD(lap���\�b�h�e�X�g){
			writeMessage("In lap���\�b�h�e�X�g");

			const long LAP_TIME = 10;
			long lap_time;

			writeMessage("RESET��Ԏ��̊m�F",1);
			Assert::AreEqual(-1L,timer.lap()
							,L"RESET->lap()",LINE_INFO());
			Assert::AreEqual(-1L,timer.lap(LAP_TIME)
							,L"RESET->lap(LAP_TIME)",LINE_INFO());
			Assert::IsTrue(timer.getLapTime().empty()
							,L"RESET->getLapTime()",LINE_INFO());


			writeMessage("START��Ԏ��̊m�F",1);
			timer.start();
			Assert::AreNotEqual(-1L,timer.lap()
							,L"START->lap()",LINE_INFO());
			Assert::IsFalse(timer.getLapTime().empty()
							,L"START->getLapTime()",LINE_INFO());
			Assert::AreEqual(timer.getNow(),timer.lap()
							,L"START->lap()",LINE_INFO());
			while(timer.getDiff() < LAP_TIME);
			Assert::AreNotEqual(-1L,timer.lap(LAP_TIME)
							,L"START->lap(LAP_TIME)",LINE_INFO());
			while(timer.getDiff() < LAP_TIME);
			lap_time = timer.getLapTime().back() + LAP_TIME;
			Assert::AreEqual(lap_time,timer.lap(LAP_TIME)
							,L"START->lap(LAP_TIME)",LINE_INFO());

			writeMessage("��O�����m�F",2);
			try{
				timer.lap(LAP_TIME);
				Assert::Fail(L"lap(LAP_TIME)�̗�O",LINE_INFO());
			}catch(pro::OutOfRangeException<long> e){
				writeMessage(e.what(),2);
			}
			try{
				timer.lap(-(LAP_TIME));
				Assert::Fail(L"lap(-LAP_TIME)�̗�O",LINE_INFO());
			}catch(pro::OutOfRangeException<long> e){
				writeMessage(e.what(),2);
			}

			
			writeMessage("STOP��Ԏ��̊m�F",1);
			timer.stop();
			lap_time = timer.lap();
			Assert::AreEqual(timer.getNow(),lap_time
							,L"START->lap()",LINE_INFO());

			writeMessage("��O�����m�F",2);
			try{
				timer.lap();
				Assert::Fail(L"lap()�̗�O",LINE_INFO());
			}catch(pro::Exception e){
				writeMessage(e.what(),2);
			}
			try{
				timer.lap(LAP_TIME);
				Assert::Fail(L"lap(LAP_TIME)�̗�O",LINE_INFO());
			}catch(pro::OutOfRangeException<long> e){
				writeMessage(e.what(),2);
			}
			try{
				timer.lap(-(LAP_TIME));
				Assert::Fail(L"lap(-LAP_TIME)�̗�O",LINE_INFO());
			}catch(pro::OutOfRangeException<long> e){
				writeMessage(e.what(),2);
			}

		}

		TEST_METHOD(getDiff���\�b�h�e�X�g){
			writeMessage("In getDiff���\�b�h�e�X�g");
			
			writeMessage("RESET��Ԏ��̊m�F",1);
			Assert::AreEqual(-1L,timer.getDiff()
							,L"RESET->getDiff()",LINE_INFO());


			writeMessage("lap�O��START��Ԏ��̊m�F",1);
			timer.start();
			Assert::AreEqual(timer.getNow(),timer.getDiff()
							,L"START->getDiff()",LINE_INFO());


			writeMessage("lap�O��STOP��Ԏ��̊m�F",1);
			timer.stop();
			Assert::AreEqual(timer.getNow(),timer.getDiff()
							,L"STOP->getDiff()",LINE_INFO());


			writeMessage("lap�O��RESTART���̊m�F",1);
			timer.restart();
			Assert::AreEqual(timer.getNow(),timer.getDiff()
							,L"RESTART->getDiff()",LINE_INFO());

			
			writeMessage("lap���START��Ԏ��̊m�F",1);
			timer.lap();
			Assert::AreEqual(timer.getNow()-timer.getLapTime().back(),timer.getDiff()
							,L"START->getDiff()",LINE_INFO());


			writeMessage("lap���STOP��Ԏ��̊m�F",1);
			timer.stop();
			Assert::AreEqual(timer.getNow()-timer.getLapTime().back(),timer.getDiff()
							,L"STOP->getDiff()",LINE_INFO());


			writeMessage("lap���RESTART��Ԏ��̊m�F",1);
			timer.restart();
			Assert::AreEqual(timer.getNow()-timer.getLapTime().back(),timer.getDiff()
							,L"RESTART->getDiff()",LINE_INFO());


			writeMessage("RESET��Ԏ��̊m�F",1);
			timer.reset();
			Assert::AreEqual(-1L,timer.getDiff()
							,L"RESTART->getDiff()",LINE_INFO());

		}

		TEST_METHOD(getNow���\�b�h�e�X�g){
			writeMessage("In getNow���\�b�h�e�X�g");

			writeMessage("RESET��Ԏ��̊m�F",1);
			Assert::AreEqual(-1L,timer.getNow()
							,L"RESET->getNow()",LINE_INFO());


			writeMessage("START��Ԏ��̊m�F",1);
			timer.start();
			Assert::AreEqual(clock() - timer.getStartTime(),timer.getNow()
							,L"START->getNow()",LINE_INFO());


			writeMessage("STOP��Ԏ��̊m�F",1);
			timer.stop();
			Assert::AreEqual(timer.getStopTime() - timer.getStartTime(),timer.getNow()
							,L"STOP->getNow()",LINE_INFO());


			writeMessage("RESTART���̊m�F",1);
			timer.restart();
			Assert::AreEqual(clock() - timer.getSumStop() - timer.getStartTime()
							,timer.getNow()
							,L"RESTART->getNow()",LINE_INFO());

			
			writeMessage("RESET��Ԏ��̊m�F",1);
			timer.reset();
			Assert::AreEqual(-1L,timer.getNow()
							,L"RESET->getNow()",LINE_INFO());
		}


		//	TEST_METHOD(TimerNomal)
		//{
		//	Logger::WriteMessage("In TimerNomal");
		//	pro::Timer timer;
		//	//�R���X�g���N�^�ɂ�鏉����
		//	Assert::AreEqual(-1,static_cast<int>(timer.getStartTime()),L"���sgetState()");
		//	Assert::AreEqual(-1,static_cast<int>(timer.getStopTime()),L"���sgetState()");
		//	Assert::AreEqual(0,static_cast<int>(timer.getSumStop()),L"���sgetState()");

		//	Assert::AreEqual(static_cast<int>( timer.m_sec(2) ),2000,L"m_sec");

		//	timer.setState(pro::Timer::RESET);
		//	Assert::AreEqual(static_cast<int>(pro::Timer::RESET),static_cast<int>(timer.getState()),L"���sgetState()");
		//	timer.start();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::START),static_cast<int>(timer.getState()),L"���sstart ==");
		//	timer.stop();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::STOP),static_cast<int>(timer.getState()),L"���sstop ==");
		//	timer.restart();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::START),static_cast<int>(timer.getState()),L"���srestart ==");
		//	timer.reset();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::RESET),static_cast<int>(timer.getState()),L"���sreset"); 

		//	/*restart �e�X�g�ǂ����悤
		//	 lap getDiff lap_time.back()���ꉽ
		//	Assert::AreEqual(3,3,
		//		// Tolerance:
		//		0.01,
		//		// Message:
		//		L"Basic test failed",
		//		// Line number - used if there is no PDB file:
		//		LINE_INFO());:*/			
	
		//}	
		//TEST_METHOD(TimerAbso)
		//{
		//	Logger::WriteMessage("In TimerAbso");
		//	pro::Timer timer;
		//	//�{�P����
		//	timer.reset();
		//	Assert::AreEqual(static_cast<int>(timer.stop()),static_cast<int>(-1),L"���sstop -1");
		//	Assert::AreEqual(static_cast<int>(timer.restart()),static_cast<int>(-1),L"���srestart -1");
		//	Assert::AreEqual(static_cast<int>(timer.lap()),static_cast<int>(-1),L"���slap() -1");
		//	Assert::AreEqual(static_cast<int>(timer.getDiff()),static_cast<int>(-1),L"���s getDiff() -1");
		//	Assert::AreEqual(static_cast<int>(timer.getNow()),static_cast<int>(-1),L"���s getNow() -1"); 
		//}	
		//TEST_METHOD(Timervalue)
		//{
		//	pro::Timer timer;
		//	timer.reset();
		//	timer.start();
		//	Assert::IsTrue(static_cast<int>(timer.stop())<=static_cast<int>(timer.getNow())+5 && static_cast<int>(timer.stop())>=static_cast<int>(timer.getNow()),L"���s getNow() -1");
		//	timer.reset();
		//	timer.start();
		//	int sum=clock();
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.restart())<=static_cast<int>(clock()-timer.getStopTime())-sum+5 && static_cast<int>(timer.restart())>=static_cast<int>(clock()-timer.getStopTime())-sum,L"���s getNow() -1");
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(clock() -timer. getStopTime() - timer.getStartTime())+5 && static_cast<int>(timer.getNow())>=static_cast<int>(clock() -timer. getStopTime() - timer.getStartTime()),L"���s getNow() -1");
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime())+5 && static_cast<int>(timer.getNow())>=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime()),L"���s getNow() -1");
		//}
		//TEST_METHOD(TimerVeror)
		//{
		//	Logger::WriteMessage("In TimerVeror");
		//	pro::Timer timer;
		//	try
		//	{
		//		timer.lap(-1);
		//		Assert::IsTrue(0<1);
		//	}
		//	catch(pro::OutOfRangeException<long> e){
		//		e.showError();
		//	}	
		//}

		//TEST_METHOD(TimerValue)
		//{
		//	Logger::WriteMessage("In TimerValue");
		//	pro::Timer timer;
		//	timer.reset();
		//	timer.start();
		//	//Assert::IsTrue(static_cast<int>(timer.stop())<=static_cast<int>(timer.getNow())+5
		//	//			&& static_cast<int>(timer.stop())>=static_cast<int>(timer.getNow())
		//	//				,L"���s getNow()1 -1",LINE_INFO());
		//	timer.reset();
		//	timer.start();
		//	int sum=clock();
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.restart())<=static_cast<int>(clock()-timer.getStopTime())-sum+5 
		//				&& static_cast<int>(timer.restart())>=static_cast<int>(clock()-timer.getStopTime())-sum,L"���s getNow()2 -1",LINE_INFO());
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(clock() -timer. getSumStop() - timer.getStartTime())+5 
		//				&& static_cast<int>(timer.getNow())>=static_cast<int>(clock() -timer. getSumStop() - timer.getStartTime()),L"���s getNow()3 -1",LINE_INFO());
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime())+5 
		//				&& static_cast<int>(timer.getNow())>=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime()),L"���s getNow()4 -1",LINE_INFO());
		//}



	};
}