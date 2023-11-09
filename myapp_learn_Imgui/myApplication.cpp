#include "myApplication.h"

namespace MyApp
{

    void readerUI()
    {

        //菜单
        static bool show_calculator_window = false;
        static bool show_another_window = false;
        static bool show_calculator_for_date = false;


        ImGui::Begin("test1");
        if (ImGui::CollapsingHeader("my tools"))
        {
            ImGui::Text("This is a menu, created by rebotzz.");
            //ImGui::Text("中文测试");

            if (ImGui::BeginTable("split", 2))
            {
                ImGui::TableNextColumn(); ImGui::Checkbox("calculator", &show_calculator_window);
                ImGui::TableNextColumn(); ImGui::Checkbox("calculator for date", &show_calculator_for_date);

                ImGui::EndTable();
            }

            static float f = 0.0f;
            static int counter = 0;
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            if (ImGui::CollapsingHeader("tool 2"))
            {
                ImGui::Text("wait to develop");
                static bool option_a = false;
                static bool option_b = false;

                if (ImGui::BeginTable("split", 3))
                {
                    ImGui::TableNextColumn(); ImGui::Checkbox("a", &option_a);
                    ImGui::TableNextColumn(); ImGui::Checkbox("b", &option_b);

                    ImGui::EndTable();
                }
            }

            ImGui::Checkbox("Another Window", &show_another_window);

        }
        if (ImGui::CollapsingHeader("my first tool"))
        {
            ImGui::Text("hey, guys,it's so cool.");
            static bool button_my_first_tool = false;
            ImGui::Checkbox("open my first tool", &button_my_first_tool);
            if (button_my_first_tool)
            {
                my_first_tool();
            }
        }

        static bool no_showDemo = false;
        static bool no_nothing = false;
        if (ImGui::CollapsingHeader("Window options"))
        {
            ImGui::Text("waiting for develop");
            if (ImGui::BeginTable("split", 3))
            {
                ImGui::TableNextColumn(); ImGui::Checkbox("Setting Demo", &no_showDemo);
                ImGui::TableNextColumn(); ImGui::Checkbox("Nothing", &no_nothing);

                ImGui::EndTable();
            }
            if (no_showDemo)
            {
                ImGui::ShowDemoWindow();
            }
        }

        ImGui::End();

        //计算器
        if (show_calculator_window)
        {
            ImGui::Begin("calculator", &show_calculator_window);
            //static float add1 = 0.0f;       //应为一直动态刷新,所以需要static
            //static float add2 = 0.0f;
            //ImGui::DragFloat("value1", &add1);
            //ImGui::DragFloat("value2", &add2);
            static float addValue[] = { 0.0f,0.0f };
            ImGui::DragFloat2("value1,value2", addValue);

            static float sum = 0.0f;

            if (ImGui::Button("add"))
            {
                sum = addValue[0] + addValue[2];
            }
            ImGui::DragFloat("result", &sum);
            ImGui::Text("sum: %.6f", sum);
            ImGui::End();
        }

        //日期计算器
        if (show_calculator_for_date)
        {
            ImGui::Begin("calculator_for_date", &show_calculator_for_date);
            static bool button_hello = ImGui::Button("hello");
            if (button_hello)
            {
                ImGui::Text("hello too!");
                std::cout << "Button clicked!" << std::endl;

            }
            ImGui::Text("1.date +/- days:");
            ImGui::Text("input:");
            static int date_value1a[3] = { 1,1,1 };
            static int date_value1b[3] = { 1,1,1 };
            static int date_out1[4] = { 1,1,1,0 };
            static int date_days = 0;
            ImGui::DragInt3("date:year/month/day", date_value1a);
            ImGui::DragInt("days:", &date_days);

            bool date_calculate1 = ImGui::Button("calculate 1");
            if (date_calculate1)
            {
                calculator_for_date(date_value1a, date_value1b, date_out1, date_days, 0);
            }
            ImGui::Text("output:");
            ImGui::DragInt3("result date:", date_out1);

            ImGui::Text("2.date1 - date2:");
            ImGui::Text("input:");
            static int date_value2a[3] = { 1,1,1 };
            static int date_value2b[3] = { 1,1,1 };
            ImGui::DragInt3("date1:year/month/day", date_value2a);
            ImGui::DragInt3("date2:year/month/day", date_value2b);

            bool date_calculate2 = ImGui::Button("calculate 2");
            if (date_calculate2)
            {
                calculator_for_date(date_value2a, date_value2b, date_out1, date_days, 1);
            }
            ImGui::Text("output:");
            ImGui::DragInt("gap of date:", &date_out1[3]);

            ImGui::End();
        }

        //一个窗口
        if (show_another_window)
        {
            ImGui::Begin("hello", &show_another_window);

            static bool button_hello = false;
            if (ImGui::Button("hello"))
            {
                button_hello = !button_hello;
            }
            if (button_hello)
            {
                ImGui::Text("hello too!");
                //std::cout << "Button clicked!" << std::endl;

            }
            static float value = 0.0f;
            static int left_right[2] = { 0,0 };
            ImGui::SliderInt2("left and right", left_right, 0, 100);
            ImGui::End();
        }

    }


    void my_first_tool()
    {
        static bool my_tool_active;

        // Create a window called "My First Tool", with a menu bar.
        ImGui::Begin("My First Tool");
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
                if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
                if (ImGui::MenuItem("Close", "Ctrl+W")) { /*my_tool_active = false;*/ }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // Edit a color stored as 4 floats
        static float my_color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };
        ImGui::ColorEdit4("Color", my_color);

        // Generate samples and plot them
        float samples[100];
        for (int n = 0; n < 100; n++)
            samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
        ImGui::PlotLines("Samples", samples, 100);

        // Display contents in a scrolling region
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
        ImGui::BeginChild("Scrolling");
        for (int n = 0; n < 50; n++)
            ImGui::Text("%04d: Some text", n);
        ImGui::EndChild();
        ImGui::End();
    }




    void calculator_for_date(int date1[], int date2[], int out[], int days, int options)
    {
        Date d(date1[0], date1[1], date1[2]);
        Date d1(date2[0], date2[1], date2[2]);
        int day = days;
        //周几
        char week[][7] = { "周一","周二","周三" ,"周四" ,"周五" ,"周六","周天" };
        int num = 0;
        Date d0(1, 1, 1);

        //菜单
        enum MEUN_DATE
        {
            ADD_SUB_DAY_DATE,	//0
            SUB_DATE_DATE		//1
        };

        if (ADD_SUB_DAY_DATE == options)
        {
            d += day;
            num = (d - d0) % 7;
            cout << "结果:" << d << " " << week[num] << endl;
            out[0] = d._year;
            out[1] = d._month;
            out[2] = d._day;
        }

        if (SUB_DATE_DATE == options)
        {
            if (d != d1)
            {
                int tmp = d - d1;
                cout << "结果:" << tmp << "天" << endl;
                out[3] = tmp;
            }
        }
    }




    ////////////////////////////日期类方法
    inline ostream& operator<<(ostream& out, const Date& d)
    {
        out << d._year << "年" << d._month << "月" << d._day << "日";
        return out;
    }

    //运算符重载 >> ,cin属于istream类型对象
    inline istream& operator>>(istream& in, Date& d)
    {
        in >> d._year >> d._month >> d._day;
        if (!d.CheckDate())
        {
            cout << "输入日期不合法." << endl;
        }
        return in;
    }

    ////////////////////////////////////////////////日期类实现
        // 日期 == 日期
    bool Date::operator == (const Date& d) const
    {
        return _year == d._year
            && _month == d._month
            && _day == d._day;
    }

    //日期 = 日期		针对两个都已存在,d2.operator=(d1)
    Date& Date::operator=(const Date& d)
    {
        if (this != &d)	//出去自己给自己赋值
        {
            _year = d._year;
            _month = d._month;
            _day = d._day;
        }
        return *this;	//出来作用域还在,返回引用
    }

    //++日期
    Date& Date::operator++()
    {
        *this += 1;	//复用:+=日期
        return *this;
    }

    //日期++
    Date Date::operator++(int)
    {
        Date tmp = *this;
        *this += 1;		//复用:+=日期
        return tmp;
    }

    // 日期+=天数
    Date& Date::operator+=(int day)		//d.operator+=(day);
    {
        //day < 0 的情况
        // d + (-|day|) = d - |day|
        if (day < 0)
        {
            day = -day;
            *this -= day;
            return *this;
        }

        _day += day;
        int maxday = GetMonthDay(_year, _month);
        while (_day > maxday)	//调整日期,使其格式合法
        {
            _day -= maxday;
            _month++;
            if (_month > 12)
            {
                _month = 1;
                _year++;
            }
            maxday = GetMonthDay(_year, _month);
        }
        return *this;
    }
    // 日期+天数
    Date Date::operator+(int day) const
    {
        Date tmp(*this);
        tmp += day;		//复用 +=
        return tmp;
    }
    // 日期-天数
    Date Date::operator-(int day) const
    {
        Date tmp(*this);
        tmp -= day;		//复用 -=
        return tmp;
    }
    // 日期-=天数
    Date& Date::operator-=(int day)
    {
        //day < 0 天数小于0的情况
        // d - (-|day|) = d + |day|
        if (day < 0)
        {
            day = -day;
            *this += day;
            return *this;
        }

        _day -= day;
        //日期为正数:合法 ; 日期为负数,上一个月
        while (_day <= 0)
        {
            _month--;
            if (_month == 0)
            {
                _month = 12;
                _year--;
            }

            _day += GetMonthDay(_year, _month);
        }

        return *this;
    }

    // 日期--
    Date Date::operator--(int)
    {
        Date tmp = *this;
        *this -= 1;		//复用 -=
        return tmp;
    }
    // --日期
    Date& Date::operator--()
    {
        *this -= 1;		//复用 -=
        return *this;
    }

    // 日期>日期
    bool Date::operator>(const Date& d) const
    {
        if (_year > d._year)	//年大
        {
            return true;
        }
        else if (_year == d._year && _month > d._month)		//年相等,月大
        {
            return true;
        }
        else if (_year == d._year && _month == d._month && _day > d._day)	//年,月相等,天数大
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // 日期>=日期
    bool Date::operator >= (const Date& d) const
    {
        return (*this == d) || (*this > d);	//复用 == >
    }

    // 日期<日期
    bool Date::operator < (const Date& d)const
    {
        return !(*this >= d);	//复用 >=
    }
    // 日期<=日期
    bool Date::operator <= (const Date& d)const
    {
        return !(*this > d);	//复用 >
    }
    // 日期!=日期
    bool Date::operator != (const Date& d)const
    {
        return !(*this == d);	//复用 ==
    }

    // 日期-日期 返回天数	代码优化2.0
    int Date::operator-(const Date& d)const
    {
        Date max = *this;	//大日期
        Date min = d;		//小日期
        int symbol = 1;		//正负号
        int day = 0;		//相差天数
        if (max < min)
        {
            max = d;
            min = *this;
            symbol = -1;
        }

        while (max != min)
        {
            min += 1;
            day += 1;
        }
        return symbol * day;
    }
}
