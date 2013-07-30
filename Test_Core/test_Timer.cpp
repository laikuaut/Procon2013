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

		// ステータスのテストに使用
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

		//BEGIN_TEST_METHOD_ATTRIBUTE(コンストラクタ初期値)
		//	TEST_PRIORITY(1)
		//END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD_INITIALIZE(TestInitialize){

		}

		TEST_METHOD_CLEANUP(TestCleanup){
			timer.reset();
		}

		TEST_METHOD(コンストラクタ初期値){
			writeMessage("In コンストラクタ初期値");

			pro::Timer timer;

			writeMessage("コンストラクタによる初期値",1);
			Assert::AreEqual(-1L,timer.getStartTime()
							,L"start_time != -1",LINE_INFO());
			Assert::AreEqual(-1L,timer.getStopTime()
							,L"stop_time != -1",LINE_INFO());
			Assert::AreEqual(0L,timer.getSumStop()
							,L"sum_stop != 0",LINE_INFO());

			writeMessage("コンストラクタ初期のステータス",1);
			checkState(pro::Timer::RESET,L"state != RESET");

			// ラップ用変数作成
			vector<clock_t> lap;
			const type_info& info = typeid(lap);

			writeMessage("型チェック",1);
			Assert::IsTrue(info==typeid(timer.getLapTime())
							,L"型がvector<clock_t>でありません",LINE_INFO());

			writeMessage("ラップ初期化の確認",1);
			lap = timer.getLapTime();
			Assert::IsTrue(lap.empty()
							,L"lapが空でありません",LINE_INFO());
		
		}

		TEST_METHOD(ステータスの値を確認){
			writeMessage("In ステータスの値を確認");

			writeMessage("標準的な流れのテスト",1);
			timer.start();
			checkState(pro::Timer::START,L"RESET->start()");
			timer.stop();
			checkState(pro::Timer::STOP,L"START->stop()");
			timer.restart();
			checkState(pro::Timer::START,L"STOP->restart()");
			timer.reset();
			checkState(pro::Timer::RESET,L"START->reset()");

			writeMessage("RESET状態からの遷移",1);
			timer.stop();
			checkState(pro::Timer::RESET,L"RESET->stop()");
			timer.restart();
			checkState(pro::Timer::RESET,L"RESET->restart()");
			timer.reset();
			checkState(pro::Timer::RESET,L"RESET->reset()");
			timer.start();
			checkState(pro::Timer::START,L"RESET->start()");

			writeMessage("START状態からの遷移",1);
			timer.start();
			checkState(pro::Timer::START,L"START->start()");
			timer.restart();
			checkState(pro::Timer::START,L"START->restart()");
			timer.reset();
			checkState(pro::Timer::RESET,L"START->reset()");

			writeMessage("STOP状態からの遷移",1);
			timer.start();
			timer.stop();
			timer.reset();
			checkState(pro::Timer::RESET,L"STOP->reset()");
			timer.start();
			timer.stop();
			timer.start();
			checkState(pro::Timer::START,L"STOP->start()");

		}

		TEST_METHOD(m_secメソッドテスト){
			writeMessage("In m_secメソッドテスト");
			
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
							,L"pro::Timer::PER_SECと一致しない",LINE_INFO());
			
			writeMessage(clock_per_sec_str,1);
			Assert::AreEqual(static_cast<long>(CLOCKS_PER_SEC),pro::Timer::m_sec(1)
							,L"CLOCKS_PER_SECと一致しない",LINE_INFO());
		}

		TEST_METHOD(startメソッドテスト){
			writeMessage("In startメソッドテスト");
			
			long start_time;

			writeMessage("stateの確認は ステータスの値を確認() を実行すること",1);


			writeMessage("標準的な流れのstart_timeの値確認",1);
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


			writeMessage("2回目のstart()と1回目のstart()の比較",1);
			timer.start();
			while(start_time==clock());
			Assert::IsTrue(start_time < timer.getStartTime()
							,L"2回目のstart()と一回目のstart()の比較",LINE_INFO());

		}

		TEST_METHOD(stopメソッドテスト){
			writeMessage("In stopメソッドテスト");

			writeMessage("stateの確認は ステータスの値を確認() を実行すること",1);

			long stop_time;

			writeMessage("値変化の確認",1);
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


			writeMessage("stopの2回連続使用",1);
			timer.start();
			stop_time = timer.stop();
			Assert::AreEqual(-1L,timer.stop()
							,L"2回目連続のstopの返り値",LINE_INFO());
			Assert::AreEqual(stop_time,timer.getStopTime()
							,L"2回目連続のstopでもstop_timeの値は変化しない",LINE_INFO());

			
			writeMessage("stopの2回目以降の使用",1);
			timer.restart();
			while(stop_time==clock());
			Assert::IsTrue(stop_time<timer.stop()
							,L"2回目の使用でstop_timeの変化確認(restart)",LINE_INFO());
			timer.start();
			Assert::IsTrue(stop_time<timer.stop()
							,L"2回目の使用でstop_timeの変化確認(start)",LINE_INFO());


		}

		TEST_METHOD(restartメソッドテスト){
			writeMessage("In restartメソッドテスト");

			writeMessage("stateの確認は ステータスの値を確認() を実行すること",1);

			long stop_time,sum_stop;


			writeMessage("値変化の確認",1);
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

			
			writeMessage("2回目以降のsum_stop増加確認",1);
			sum_stop = timer.getSumStop();
			stop_time = timer.stop();
			while(stop_time==clock());
			Assert::IsTrue(sum_stop<timer.restart()
							,L"STOP->restart()",LINE_INFO());
			Assert::IsTrue(sum_stop<timer.getSumStop()
							,L"STOP->restart()",LINE_INFO());

		}

		TEST_METHOD(resetメソッドテスト){
			writeMessage("In resetメソッドテスト");

			writeMessage("stateの確認は ステータスの値を確認() を実行すること",1);

			long stop_time;

			
			writeMessage("値変化の確認(start,sum_stop,lap)",1);
			timer.start();
			stop_time = timer.stop();
			while(stop_time == clock());
			timer.restart();
			timer.lap();
			Assert::AreNotEqual(-1L,timer.getStartTime()
							,L"start_time変化",LINE_INFO());
			Assert::AreNotEqual(0L,timer.getSumStop()
							,L"sum_stop変化",LINE_INFO());
			Assert::IsFalse(timer.getLapTime().empty()
							,L"lap変化",LINE_INFO());

			
			writeMessage("restによる初期化確認",1);
			timer.reset();
			Assert::AreEqual(-1L,timer.getStartTime()
							,L"start_time初期化",LINE_INFO());
			Assert::AreEqual(0L,timer.getSumStop()
							,L"sum_stop初期化",LINE_INFO());
			Assert::IsTrue(timer.getLapTime().empty()
							,L"lap初期化",LINE_INFO());

			
			writeMessage("値変化の確認(stop)",1);
			timer.start();
			timer.stop();
			Assert::AreNotEqual(-1L,timer.getStopTime()
							,L"stop_time変化",LINE_INFO());
			
			
			writeMessage("restによる初期化確認",1);
			timer.reset();
			Assert::AreEqual(-1L,timer.getStopTime()
							,L"stop_time初期化",LINE_INFO());


		}

		TEST_METHOD(lapメソッドテスト){
			writeMessage("In lapメソッドテスト");

			const long LAP_TIME = 10;
			long lap_time;

			writeMessage("RESET状態時の確認",1);
			Assert::AreEqual(-1L,timer.lap()
							,L"RESET->lap()",LINE_INFO());
			Assert::AreEqual(-1L,timer.lap(LAP_TIME)
							,L"RESET->lap(LAP_TIME)",LINE_INFO());
			Assert::IsTrue(timer.getLapTime().empty()
							,L"RESET->getLapTime()",LINE_INFO());


			writeMessage("START状態時の確認",1);
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

			writeMessage("例外処理確認",2);
			try{
				timer.lap(LAP_TIME);
				Assert::Fail(L"lap(LAP_TIME)の例外",LINE_INFO());
			}catch(pro::OutOfRangeException<long> e){
				writeMessage(e.what(),2);
			}
			try{
				timer.lap(-(LAP_TIME));
				Assert::Fail(L"lap(-LAP_TIME)の例外",LINE_INFO());
			}catch(pro::OutOfRangeException<long> e){
				writeMessage(e.what(),2);
			}

			
			writeMessage("STOP状態時の確認",1);
			timer.stop();
			lap_time = timer.lap();
			Assert::AreEqual(timer.getNow(),lap_time
							,L"START->lap()",LINE_INFO());

			writeMessage("例外処理確認",2);
			try{
				timer.lap();
				Assert::Fail(L"lap()の例外",LINE_INFO());
			}catch(pro::Exception e){
				writeMessage(e.what(),2);
			}
			try{
				timer.lap(LAP_TIME);
				Assert::Fail(L"lap(LAP_TIME)の例外",LINE_INFO());
			}catch(pro::OutOfRangeException<long> e){
				writeMessage(e.what(),2);
			}
			try{
				timer.lap(-(LAP_TIME));
				Assert::Fail(L"lap(-LAP_TIME)の例外",LINE_INFO());
			}catch(pro::OutOfRangeException<long> e){
				writeMessage(e.what(),2);
			}

		}

		TEST_METHOD(getDiffメソッドテスト){
			writeMessage("In getDiffメソッドテスト");
			
			writeMessage("RESET状態時の確認",1);
			Assert::AreEqual(-1L,timer.getDiff()
							,L"RESET->getDiff()",LINE_INFO());


			writeMessage("lap前のSTART状態時の確認",1);
			timer.start();
			Assert::AreEqual(timer.getNow(),timer.getDiff()
							,L"START->getDiff()",LINE_INFO());


			writeMessage("lap前のSTOP状態時の確認",1);
			timer.stop();
			Assert::AreEqual(timer.getNow(),timer.getDiff()
							,L"STOP->getDiff()",LINE_INFO());


			writeMessage("lap前のRESTART時の確認",1);
			timer.restart();
			Assert::AreEqual(timer.getNow(),timer.getDiff()
							,L"RESTART->getDiff()",LINE_INFO());

			
			writeMessage("lap後のSTART状態時の確認",1);
			timer.lap();
			Assert::AreEqual(timer.getNow()-timer.getLapTime().back(),timer.getDiff()
							,L"START->getDiff()",LINE_INFO());


			writeMessage("lap後のSTOP状態時の確認",1);
			timer.stop();
			Assert::AreEqual(timer.getNow()-timer.getLapTime().back(),timer.getDiff()
							,L"STOP->getDiff()",LINE_INFO());


			writeMessage("lap後のRESTART状態時の確認",1);
			timer.restart();
			Assert::AreEqual(timer.getNow()-timer.getLapTime().back(),timer.getDiff()
							,L"RESTART->getDiff()",LINE_INFO());


			writeMessage("RESET状態時の確認",1);
			timer.reset();
			Assert::AreEqual(-1L,timer.getDiff()
							,L"RESTART->getDiff()",LINE_INFO());

		}

		TEST_METHOD(getNowメソッドテスト){
			writeMessage("In getNowメソッドテスト");

			writeMessage("RESET状態時の確認",1);
			Assert::AreEqual(-1L,timer.getNow()
							,L"RESET->getNow()",LINE_INFO());


			writeMessage("START状態時の確認",1);
			timer.start();
			Assert::AreEqual(clock() - timer.getStartTime(),timer.getNow()
							,L"START->getNow()",LINE_INFO());


			writeMessage("STOP状態時の確認",1);
			timer.stop();
			Assert::AreEqual(timer.getStopTime() - timer.getStartTime(),timer.getNow()
							,L"STOP->getNow()",LINE_INFO());


			writeMessage("RESTART時の確認",1);
			timer.restart();
			Assert::AreEqual(clock() - timer.getSumStop() - timer.getStartTime()
							,timer.getNow()
							,L"RESTART->getNow()",LINE_INFO());

			
			writeMessage("RESET状態時の確認",1);
			timer.reset();
			Assert::AreEqual(-1L,timer.getNow()
							,L"RESET->getNow()",LINE_INFO());
		}


		//	TEST_METHOD(TimerNomal)
		//{
		//	Logger::WriteMessage("In TimerNomal");
		//	pro::Timer timer;
		//	//コンストラクタによる初期化
		//	Assert::AreEqual(-1,static_cast<int>(timer.getStartTime()),L"失敗getState()");
		//	Assert::AreEqual(-1,static_cast<int>(timer.getStopTime()),L"失敗getState()");
		//	Assert::AreEqual(0,static_cast<int>(timer.getSumStop()),L"失敗getState()");

		//	Assert::AreEqual(static_cast<int>( timer.m_sec(2) ),2000,L"m_sec");

		//	timer.setState(pro::Timer::RESET);
		//	Assert::AreEqual(static_cast<int>(pro::Timer::RESET),static_cast<int>(timer.getState()),L"失敗getState()");
		//	timer.start();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::START),static_cast<int>(timer.getState()),L"失敗start ==");
		//	timer.stop();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::STOP),static_cast<int>(timer.getState()),L"失敗stop ==");
		//	timer.restart();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::START),static_cast<int>(timer.getState()),L"失敗restart ==");
		//	timer.reset();
		//	Assert::AreEqual(static_cast<int>(pro::Timer::RESET),static_cast<int>(timer.getState()),L"失敗reset"); 

		//	/*restart テストどうしよう
		//	 lap getDiff lap_time.back()これ何
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
		//	//ボケ処理
		//	timer.reset();
		//	Assert::AreEqual(static_cast<int>(timer.stop()),static_cast<int>(-1),L"失敗stop -1");
		//	Assert::AreEqual(static_cast<int>(timer.restart()),static_cast<int>(-1),L"失敗restart -1");
		//	Assert::AreEqual(static_cast<int>(timer.lap()),static_cast<int>(-1),L"失敗lap() -1");
		//	Assert::AreEqual(static_cast<int>(timer.getDiff()),static_cast<int>(-1),L"失敗 getDiff() -1");
		//	Assert::AreEqual(static_cast<int>(timer.getNow()),static_cast<int>(-1),L"失敗 getNow() -1"); 
		//}	
		//TEST_METHOD(Timervalue)
		//{
		//	pro::Timer timer;
		//	timer.reset();
		//	timer.start();
		//	Assert::IsTrue(static_cast<int>(timer.stop())<=static_cast<int>(timer.getNow())+5 && static_cast<int>(timer.stop())>=static_cast<int>(timer.getNow()),L"失敗 getNow() -1");
		//	timer.reset();
		//	timer.start();
		//	int sum=clock();
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.restart())<=static_cast<int>(clock()-timer.getStopTime())-sum+5 && static_cast<int>(timer.restart())>=static_cast<int>(clock()-timer.getStopTime())-sum,L"失敗 getNow() -1");
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(clock() -timer. getStopTime() - timer.getStartTime())+5 && static_cast<int>(timer.getNow())>=static_cast<int>(clock() -timer. getStopTime() - timer.getStartTime()),L"失敗 getNow() -1");
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime())+5 && static_cast<int>(timer.getNow())>=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime()),L"失敗 getNow() -1");
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
		//	//				,L"失敗 getNow()1 -1",LINE_INFO());
		//	timer.reset();
		//	timer.start();
		//	int sum=clock();
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.restart())<=static_cast<int>(clock()-timer.getStopTime())-sum+5 
		//				&& static_cast<int>(timer.restart())>=static_cast<int>(clock()-timer.getStopTime())-sum,L"失敗 getNow()2 -1",LINE_INFO());
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(clock() -timer. getSumStop() - timer.getStartTime())+5 
		//				&& static_cast<int>(timer.getNow())>=static_cast<int>(clock() -timer. getSumStop() - timer.getStartTime()),L"失敗 getNow()3 -1",LINE_INFO());
		//	timer.stop();
		//	Assert::IsTrue(static_cast<int>(timer.getNow())<=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime())+5 
		//				&& static_cast<int>(timer.getNow())>=static_cast<int>(timer. getStopTime() - timer.getSumStop() - timer.getStartTime()),L"失敗 getNow()4 -1",LINE_INFO());
		//}



	};
}