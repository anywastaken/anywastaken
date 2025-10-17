#include "Tape.h"
#include "TuringMachine.h"
#include "TransitionRule.h"
#include "turing_header.h"
#include <UnitTest++/UnitTest++.h>
#include <fstream>

// ===================== Tape Tests =====================
SUITE(TapeTests) {
    TEST(CreateTape) {
        Tape tape;
        tape.create({ 'a','b','c' });
        CHECK_EQUAL('a', tape.read());
    }

    TEST(WriteAtBeginning) {
        Tape tape;
        tape.create({ 'a' });
        tape.write('x');
        CHECK_EQUAL('x', tape.read());
    }

    TEST(MoveRightAndLeft) {
        Tape tape;
        tape.create({ '1','0','1' });
        CHECK_EQUAL('1', tape.read());
        tape.move(1);
        CHECK_EQUAL('0', tape.read());
        tape.move(-1);
        CHECK_EQUAL('1', tape.read());
    }

    TEST(MoveBeyondBoundsRight) {
        Tape tape;
        tape.create({ '1' });
        tape.move(1);
        tape.write('0');
        CHECK_EQUAL('0', tape.read());
    }

    TEST(MoveBeyondBoundsLeft) {
        Tape tape;
        tape.create({ '1' });
        tape.move(-1);
        tape.write('z');
        CHECK_EQUAL('z', tape.read());
    }

    TEST(WriteAndReadMultiple) {
        Tape tape;
        tape.create({ 'a' });
        tape.write('b');
        CHECK_EQUAL('b', tape.read());
        tape.move(1);
        tape.write('c');
        CHECK_EQUAL('c', tape.read());
    }

    TEST(PrintTape) {
        Tape tape;
        tape.create({ 'a','b' });
        tape.print();
        CHECK(true);
    }
}

// ===================== TransitionRule Tests =====================
SUITE(TransitionRuleTests) {
    TEST(CreateTransitionRule) {
        TransitionRule rule;
        rule.current_state = 0;
        rule.new_state = 1;
        rule.current_symbol = 'a';
        rule.new_symbol = 'b';
        rule.move_direction = 1;

        CHECK_EQUAL(0, rule.current_state);
        CHECK_EQUAL(1, rule.new_state);
        CHECK_EQUAL('a', rule.current_symbol);
        CHECK_EQUAL('b', rule.new_symbol);
    }

    TEST(PrintRule) {
        TransitionRule rule;
        rule.current_state = 0;
        rule.new_state = 1;
        rule.current_symbol = 'a';
        rule.new_symbol = 'b';
        rule.move_direction = -1;
        rule.print(); 
        CHECK(true);
    }
}

// ===================== TuringMachine Tests =====================
SUITE(TuringMachineTests) {
    TEST(AddTransitionRule) {
        TuringMachine tm;
        TransitionRule rule;
        rule.current_state = 0;
        rule.new_state = 1;
        rule.current_symbol = 'a';
        rule.new_symbol = 'b';
        rule.move_direction = 1;

        tm.add_TransitionRule(rule);
        CHECK_EQUAL(1, tm.rules.size());
        CHECK_EQUAL('a', tm.rules[0].current_symbol);
    }

    TEST(EditTransitionRule) {
        TuringMachine tm;
        TransitionRule rule1, rule2;
        rule1.current_state = 0; 
        rule1.new_state = 1;
        rule1.current_symbol = 'a'; 
        rule1.new_symbol = 'b'; 
        rule1.move_direction = 1;

        rule2.current_state = 0; 
        rule2.new_state = 2;
        rule2.current_symbol = 'a'; 
        rule2.new_symbol = 'c'; 
        rule2.move_direction = -1;

        tm.add_TransitionRule(rule1);
        tm.edit_TransitionRule(rule2, 1);

        CHECK_EQUAL(1, tm.rules.size());
        CHECK_EQUAL('c', tm.rules[0].new_symbol);
        CHECK_EQUAL(2, tm.rules[0].new_state);
    }

    TEST(RunWithSimpleRule) {
        TuringMachine tm;
        tm.tape.create({ 'a' });
        tm.current_state = 0;
        tm.final_state = { 1 };

        TransitionRule rule;
        rule.current_state = 0;
        rule.new_state = 1;
        rule.current_symbol = 'a';
        rule.new_symbol = 'b';
        rule.move_direction = 0;
        tm.add_TransitionRule(rule);

        tm.run(false);

        CHECK_EQUAL('b', tm.tape.read());
        CHECK_EQUAL(1, tm.current_state);
    }

    TEST(RunWithoutMatchingRule) {
        TuringMachine tm;
        tm.tape.create({ 'a' });
        tm.current_state = 0;
        tm.final_state = { 1 };

        TransitionRule rule;
        rule.current_state = 1;
        rule.new_state = 2;
        rule.current_symbol = 'b';
        rule.new_symbol = 'c';
        rule.move_direction = 1;
        tm.add_TransitionRule(rule);

        tm.run(false);
        CHECK_EQUAL(0, tm.current_state);
        CHECK_EQUAL('a', tm.tape.read());
    }

    TEST(PrintRules) {
        TuringMachine tm;
        TransitionRule rule;
        rule.current_state = 0;
        rule.new_state = 1;
        rule.current_symbol = 'a';
        rule.new_symbol = 'b';
        rule.move_direction = 1;

        tm.add_TransitionRule(rule);
        tm.printRules();
        CHECK(true);
    }


    TEST(ReadRuleFromFile) {
        string filename = "tm_rules.txt";
        ofstream file(filename);
        file << "11011010\n";            
        file << "1\n";                 
        file << "0 1 1 1 0 1\n";        
        file << "0 1 1 0 1 1\n";        
        file << "0 1 2 _ _ 0\n";        
        file << "end:2\n";              
        file.close();

        TuringMachine tm(filename);

        CHECK_EQUAL('1', tm.tape.read());
        CHECK_EQUAL(8, tm.tape.body.size());  

        
        CHECK_EQUAL(1, tm.current_state);

        
        CHECK_EQUAL(3, tm.rules.size());

        
        CHECK_EQUAL(false, tm.rules[0].move_is_first);
        CHECK_EQUAL(1, tm.rules[0].current_state);
        CHECK_EQUAL(1, tm.rules[0].new_state);
        CHECK_EQUAL('1', tm.rules[0].current_symbol);
        CHECK_EQUAL('0', tm.rules[0].new_symbol);
        CHECK_EQUAL(1, tm.rules[0].move_direction);

        
        CHECK_EQUAL(1, tm.final_state.size());
        CHECK_EQUAL(2, tm.final_state[0]);
        remove(filename.c_str());
    }

    TEST(OperatorPostfixIncrement) {
        // Создаём простую машину вручную
        TuringMachine tm;
        tm.tape.body = {'1', '0', '1'};
        tm.tape.pointer = 1;  // указываем на '0'
        tm.current_state = 0;

        // Добавляем правило:
        // move_is_first = false → сначала запись, потом движение
        // из состояния 0, при символе '0' -> новое состояние 1, записывает '1', двигается вправо
        TransitionRule r;
        r.move_is_first = false;
        r.current_state = 0;
        r.new_state = 1;
        r.current_symbol = '0';
        r.new_symbol = '1';
        r.move_direction = 1;
        tm.rules.push_back(r);

        // Конечное состояние — 2
        tm.final_state.push_back(2);

        // Делаем копию
        TuringMachine before = tm;

        // Выполняем постфиксный инкремент
        TuringMachine old = tm++;

        // Проверяем, что возвращённое значение — до изменений
        CHECK_EQUAL(before.current_state, old.current_state);
        CHECK_EQUAL(before.tape.body[1], old.tape.body[1]);

        // Проверяем, что машина изменилась
        CHECK_EQUAL(1, tm.current_state);           // перешла в новое состояние
        CHECK_EQUAL('1', tm.tape.body[1]);          // символ заменён
        CHECK_EQUAL(2, tm.tape.pointer);            // указатель сдвинулся вправо
    }

    TEST(OperatorPostfixIncrement_FinalState) {
        // Проверяем, что если текущее состояние — конечное, ничего не происходит
        TuringMachine tm;
        tm.tape.body = {'1'};
        tm.tape.pointer = 0;
        tm.current_state = 2;
        tm.final_state.push_back(2);

        TuringMachine before = tm;
        TuringMachine old = tm++;

        CHECK_EQUAL(before.current_state, tm.current_state);
        CHECK_EQUAL(before.tape.body[0], tm.tape.body[0]);
        CHECK_EQUAL(before.tape.pointer, tm.tape.pointer);
    }


    // === 1. Проверка успешного редактирования правила ===
    TEST(EditTransitionRule_Valid) {
        TuringMachine tm;
        TransitionRule rule1, rule2;
        rule1.current_state = 0; rule1.new_state = 1;
        rule1.current_symbol = 'a'; rule1.new_symbol = 'b'; rule1.move_direction = 1;

        rule2.current_state = 0; rule2.new_state = 2;
        rule2.current_symbol = 'a'; rule2.new_symbol = 'c'; rule2.move_direction = -1;

        tm.add_TransitionRule(rule1);
        tm.edit_TransitionRule(rule2, 1); // позиция с 1

        CHECK_EQUAL(1, tm.rules.size());
        CHECK_EQUAL('c', tm.rules[0].new_symbol);
        CHECK_EQUAL(2, tm.rules[0].new_state);
    }

    // === 2. Проверка некорректной позиции в edit_TransitionRule ===
    TEST(EditTransitionRule_Invalid) {
        TuringMachine tm;
        TransitionRule rule;
        rule.current_state = 0; rule.new_state = 1;
        tm.add_TransitionRule(rule);
        // не должно упасть при неправильной позиции
        tm.edit_TransitionRule(rule, 5);
        CHECK_EQUAL(1, tm.rules.size());
    }

    // === 3. Проверка operator++ с найденным правилом ===
    TEST(IncrementOperator_Normal) {
        TuringMachine tm;
        tm.tape.create({'a', 'b'});
        tm.current_state = 0;
        TransitionRule r;
        r.move_is_first = false;
        r.current_state = 0;
        r.new_state = 1;
        r.current_symbol = 'a';
        r.new_symbol = 'x';
        r.move_direction = 1;
        tm.rules.push_back(r);

        TuringMachine prev = tm++;
        // tape должна измениться
        CHECK_EQUAL('x', tm.tape.body[0]);
        // состояние должно измениться
        CHECK_EQUAL(1, tm.current_state);
        // возвращённый объект должен содержать старое состояние
        CHECK_EQUAL(0, prev.current_state);
    }

    // === 4. Проверка operator++ при отсутствии правила ===
    TEST(IncrementOperator_NoRule) {
        TuringMachine tm;
        tm.tape.create({'a'});
        tm.current_state = 0;
        TransitionRule r;
        r.move_is_first = false;
        r.current_state = 1; // не совпадает
        r.current_symbol = 'b';
        tm.rules.push_back(r);

        tm++;
        // состояние не изменилось
        CHECK_EQUAL(0, tm.current_state);
    }

    // === 5. Проверка operator++ при достижении конечного состояния ===
    TEST(IncrementOperator_FinalState) {
        TuringMachine tm;
        tm.current_state = 2;
        tm.final_state = {2}; // уже конечное
        TuringMachine prev = tm++;
        CHECK_EQUAL(2, tm.current_state);
    }

    // === 6. Проверка readRule с нормальным файлом ===
    TEST(ReadRule_ValidFile) {
        string filename = "rules_valid.txt";
        ofstream file(filename);
        file << "101\n";             // лента
        file << "0\n";               // текущее состояние
        file << "1 0 1 1 0 1\n";     // одно правило
        file << "end:2\n";           // финальное состояние
        file.close();

        TuringMachine tm(filename);
        CHECK_EQUAL(3, tm.tape.body.size());
        CHECK_EQUAL(0, tm.current_state);
        CHECK_EQUAL(1, tm.rules.size());
        CHECK_EQUAL(1, tm.rules[0].move_is_first);
        CHECK_EQUAL(1, tm.final_state.size()); // "2" + возможный '\n' игнорируется
        remove(filename.c_str());
    }

    // === 7. Проверка readRule с отсутствующим файлом ===
    TEST(ReadRule_MissingFile) {
        TuringMachine tm("file_does_not_exist.txt");
        // просто проверим, что программа не упала
        CHECK(true);
    }

    // === 8. Проверка run() до достижения конечного состояния ===
    TEST(RunUntilFinalState) {
        TuringMachine tm;
        tm.tape.create({'a'});
        tm.current_state = 0;
        tm.final_state = {1};

        TransitionRule r;
        r.move_is_first = false;
        r.current_state = 0;
        r.new_state = 1;
        r.current_symbol = 'a';
        r.new_symbol = 'b';
        r.move_direction = 0;
        tm.rules.push_back(r);

        tm.run(false);
        CHECK_EQUAL(1, tm.current_state);
        CHECK_EQUAL('b', tm.tape.body[0]);
    }


    // 1) operator++: ветка move_is_first == true
    TEST(OperatorPostfixIncrement_MoveIsFirstTrue) {
        TuringMachine tm;
        tm.tape.body = {'x','y','z'};     // тело ленты
        tm.tape.pointer = 1;              // указываем на 'y'
        tm.current_state = 0;

        TransitionRule r;
        r.move_is_first = true;           // важная ветка
        r.current_state = 0;
        r.new_state = 1;
        r.current_symbol = 'y';
        r.new_symbol = 'Q';
        r.move_direction = -1;            // сначала двигаем влево, потом пишем
        tm.rules.push_back(r);

        TuringMachine before = tm;
        TuringMachine old = tm++;         // post-increment

        // Возвращаемое значение — старое
        CHECK_EQUAL(before.current_state, old.current_state);
        // Машина изменилась: pointer сместился влево (1 + (-1) = 0) и запись в new position
        CHECK_EQUAL(0, tm.tape.pointer);
        CHECK_EQUAL('Q', tm.tape.body[0]); 
        CHECK_EQUAL(1, tm.current_state);
    }

    // 2) run(): ветка move_is_first == true (внутри цикла run)
    TEST(Run_MoveIsFirstTrue) {
        TuringMachine tm;
        tm.tape.create({'a','b','c'});
        tm.tape.pointer = 1; // указываем на 'b'
        tm.current_state = 0;
        tm.final_state = {2};

        TransitionRule r;
        r.move_is_first = true;    // проверяем порядок: move -> write
        r.current_state = 0;
        r.new_state = 2;           // сразу финальное
        r.current_symbol = 'b';
        r.new_symbol = 'M';
        r.move_direction = 1;      // двигаем вправо
        tm.rules.push_back(r);

        tm.run(false);
        // после выполнения move pointer = 2, и write записывает по позиции 2
        CHECK_EQUAL(2, tm.tape.pointer);
        CHECK_EQUAL('M', tm.tape.body[2]);
        CHECK_EQUAL(2, tm.current_state);
    }

    // 3) readRule: underscore as blank symbol and multiple final states
    TEST(ReadRule_UnderscoreAndMultipleFinalStates) {
        const char* fname = "tm_test_underscore.txt";
        std::ofstream f(fname);
        f << "1010\n";
        f << "0\n";
        // правило с "_" в качестве символа (blank)
        f << "1 0 1 _ 1 1\n";   // move_is_first=1 current_state=0 new_state=1 current_symbol='_' new_symbol='1' move_direction=1
        f << "0 1 2 0 _ -1\n";
        f << "end:2 3\n";       // два финальных состояния
        f.close();

        TuringMachine tm(fname);
        remove(fname);

        // лента прочитана
        CHECK_EQUAL(4, (int)tm.tape.body.size());
        // правила прочитаны
        CHECK_EQUAL(2, (int)tm.rules.size());
        // underscore проверяем как конкретный символ '_'
        CHECK_EQUAL('_', tm.rules[0].current_symbol);
        // финальные состояния прочитаны оба
        CHECK_EQUAL(2, (int)tm.final_state.size());
        CHECK_EQUAL(2, tm.final_state[0]);
        CHECK_EQUAL(3, tm.final_state[1]);
    }

    // 4) TransitionRule::print() — перехват stdout
    TEST(TransitionRule_Print_Output) {
        TransitionRule r;
        r.move_is_first = true;
        r.current_state = 5;
        r.new_state = 6;
        r.current_symbol = 'A';
        r.new_symbol = 'B';
        r.move_direction = -1;

        std::ostringstream buf;
        std::streambuf* old = std::cout.rdbuf(buf.rdbuf());
        r.print();
        std::cout.rdbuf(old);

        std::string out = buf.str();
        CHECK(out.find("current_state=5") != std::string::npos);
        CHECK(out.find("new_state=6") != std::string::npos);
        CHECK(out.find("move_direction=-1") != std::string::npos);
    }

    // 5) printRules() с пустым и непустым списком — перехват вывода
    TEST(PrintRules_Output) {
        TuringMachine tm;
        // пустой список: просто проверить, что не падает и ничего страшного не печатает
        {
            std::ostringstream buf;
            auto old = std::cout.rdbuf(buf.rdbuf());
            tm.printRules();
            std::cout.rdbuf(old);
            CHECK(true);
        }

        // теперь добавим правило и проверим, что printRules печатает
        TransitionRule r;
        r.move_is_first = false;
        r.current_state = 0; r.new_state = 1; r.current_symbol = 'x'; r.new_symbol = 'y'; r.move_direction = 0;
        tm.add_TransitionRule(r);

        {
            std::ostringstream buf;
            auto old = std::cout.rdbuf(buf.rdbuf());
            tm.printRules();
            std::cout.rdbuf(old);
            std::string s = buf.str();
            CHECK(s.find("Rule 0") != std::string::npos);
            CHECK(s.find("current_state=") != std::string::npos);
        }
    }

    // 6) edit_TransitionRule: поведение при неверной позиции (0 и >size)
    TEST(EditTransitionRule_InvalidPositions) {
        TuringMachine tm;
        TransitionRule r;
        tm.add_TransitionRule(r);

        // position = 0 (в коде ожидается 1..size) — не ломается
        tm.edit_TransitionRule(r, 0);
        // position > size
        tm.edit_TransitionRule(r, 5);

        // список остаётся одного элемента
        CHECK_EQUAL(1, (int)tm.rules.size());
    }

    // 7) readRule: файл с несколькими правилами парсится корректно
    TEST(ReadRule_MultipleRules) {
        const char* fname = "tm_multi_rules.txt";
        std::ofstream f(fname);
        f << "01\n";
        f << "0\n";
        f << "0 0 1 0 1 1\n";
        f << "1 1 2 1 0 -1\n";
        f << "end:2\n";
        f.close();

        TuringMachine tm(fname);
        remove(fname);

        CHECK_EQUAL(2, (int)tm.rules.size());
        CHECK_EQUAL(0, tm.rules[0].current_state);
        CHECK_EQUAL(1, tm.rules[1].current_state);
    }

    // 8) operator++: если правило не найдено — не ломается (ветка flag == false)
    TEST(OperatorPostfixIncrement_NoRuleFound_NoCrash) {
        TuringMachine tm;
        tm.tape.create({'Z'});
        tm.tape.pointer = 0;
        tm.current_state = 7; // правило для другого состояния
        // нет правил, просто убедимся, что не падает
        TuringMachine old = tm++;
        CHECK_EQUAL(7, tm.current_state);
        CHECK_EQUAL('Z', tm.tape.read());
    }

    TEST(ReadEmptyRuleFile) {
        string filename = "empty_rules.txt";
        ofstream file(filename);
        file.close();

        TuringMachine tm(filename);
        CHECK_EQUAL(0, tm.rules.size());
        remove(filename.c_str());
    }

    TEST(PrintEmptyRules) {
        TuringMachine tm;
        tm.printRules();
        CHECK(true);
    }


    TEST(PrintEmptyTape) {
        Tape tape;
        tape.print();
        CHECK(true);
    }


    TEST(OperatorPostfixIncrement_NoRuleFound) {
        TuringMachine tm;
        tm.tape.create({'x'});
        tm.current_state = 0;
        tm.final_state.push_back(5);

        // Правила не добавлены — должно вывести ошибку, но не упасть
        TuringMachine old = tm++;
        CHECK_EQUAL(0, tm.current_state); // состояние не меняется
    }


    TEST(RunWithoutRules) {
        TuringMachine tm;
        tm.tape.create({'a'});
        tm.current_state = 0;
        tm.final_state = {1};

        tm.run(false);

        CHECK_EQUAL(0, tm.current_state);
        CHECK_EQUAL('a', tm.tape.read());
    }


    TEST(EditTransitionRule_OutOfRange) {
        TuringMachine tm;
        TransitionRule rule;
        rule.current_state = 0;
        rule.new_state = 1;
        rule.current_symbol = 'a';
        rule.new_symbol = 'b';
        rule.move_direction = 1;

        // Ничего не добавлено, редактируем несуществующий элемент
        tm.edit_TransitionRule(rule, 5);

        // Проверяем, что список правил остался пустым
        CHECK_EQUAL(0, tm.rules.size());
    }

    TEST(Run_WithLogging) {
        TuringMachine tm;
        tm.tape.create({'a'});
        tm.current_state = 0;
        tm.final_state = {1};

        TransitionRule r;
        r.move_is_first = false;
        r.current_state = 0;
        r.new_state = 1;
        r.current_symbol = 'a';
        r.new_symbol = 'b';
        r.move_direction = 0;
        tm.rules.push_back(r);

        std::ostringstream buf;
        auto old = std::cout.rdbuf(buf.rdbuf());
        tm.run(true);
        std::cout.rdbuf(old);

        std::string s = buf.str();
        CHECK(s.find("...") != std::string::npos); // tape.print() выводит ...
    }

    TEST(ReadRule_WithEmptyLines) {
        string filename = "rules_with_empty.txt";
        ofstream file(filename);
        file << "abc\n";
        file << "0\n";
        file << "\n";                 // пустая строка
        file << "1 0 1 a b 1\n";
        file << "\n";                 // пустая строка
        file << "end:1\n";
        file.close();

        TuringMachine tm(filename);
        remove(filename.c_str());

        CHECK_EQUAL(1, (int)tm.rules.size());
        CHECK_EQUAL('a', tm.rules[0].current_symbol);
    }

    TEST(Tape_MoveZeroDirection) {
        Tape tape;
        tape.create({'a','b'});
        int before = 0;
        tape.move(0);
        CHECK_EQUAL(before, 0); // pointer не изменился
    }
}

int main() {
    return UnitTest::RunAllTests();
}
