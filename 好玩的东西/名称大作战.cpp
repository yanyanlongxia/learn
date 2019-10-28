#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
int rushu,choose1,choose2,choose3;
int doint1 ;
struct people{
    int atk,ddf,hp,iq,su;
    string name;
    int zhan,go;
    int now_hp,zd;
    bool used,dead;
    int defen;
    int score;
    bool atk_used,ddf_used;
    int BOSs;
    int Tour_Skill,ma_bi; 
}a[1001];

void voids(void);
bool panduan(void);
void pugong(int,int);              //普通攻击 
void xiaolifeidao(int,int);        //技能：小李飞刀 
void huoqiushu(int,int);           //技能：实力秒杀！！ 
void kuangbao(int);                //技能：狂暴术 
void leijishu(int,int);            //技能：雷击术 
void tiebishu(int);                //技能：铁壁术 
void bingdongshu(int,int);         //技能：冰封万里 
void color(string);                //颜色系统----- 
void zhandui(int);                 //战队系统----- (一）战队&名字绑定 
void zhandui_xun(int);             //战队系统----- (二）战队&战队名字&战队加成
void zhandui_xun2(int,int);        //同上 
void zhandui_skill(int);           //战队系统----- (三）战队&战队技能 
void wuqi_main(int);               //武器系统主函数 
void changqiongzhan(int,int);      //技能：苍穹斩 
void huifushu(int);                //技能：恢复术
void shixueyiji(int,int);          //技能：嗜血一击 
void beici(int,int);               //技能：背刺
void Slowsay(string);              //输出优化 
void moshi1(void);                 //玩家对战模式 
bool check(int);
bool comp1(people,people);
bool comp2(people,people);
void moshi2_boss();
void BOSS(int);
bool check2();
void peoples();
void BOSS_skill7(int);                //雷神Tour 专属技能 
void dead();
void BOSS_skill8(int);                //圣骑剑圣  专属技能
void write1 () ;
int main () ;

void write1 () {
    system("cls");
    Slowsay ("最近一次更新：2018/9/10\n");
    Slowsay ("更新主要内容：\n(1) 新增BOSS 雷神Tour \n(2) 新增BOSS 圣骑剑圣");
    Sleep (2500);
    main (); 
}

void BOSS_skill8(int j){
    Sleep(500);
    if(a[rushu+1].Tour_Skill==3){
        color("Y");cout<<"--千锤万载成剑心--"<<endl;Sleep(500);color("W");
        cout<<a[rushu+1].name<<"使用了---神技---";color("R");cout<<"圣剑之禁·灭世的光芒";color("W");cout<<"-----"<<endl;
        for(int l=1;l<=5;l++){Sleep(800);int shanghai=rand()%100+100;
            if(check2()==true) break;
            if(l==1){color("B");cout<<"第一式---圣剑之刃";}
            else if(l==2){color("R");cout<<"第二式---圣剑之光";}
            else if(l==3){color("G");cout<<"第三式---圣剑之威";}
            else if(l==4){color("Y");cout<<"第四式---圣剑之锋";}
            else if(l==5){color("C");cout<<"第五式---圣剑之灭";}
            int ffff=rand()%rushu+1;
            while(true){
                ffff=rand()%rushu+1;if(a[ffff].now_hp>0) break;
            }a[ffff].now_hp-=shanghai;voids();
            cout<<endl;color("W");cout<<"玩家"<<a[ffff].name<<"受到了"<<shanghai<<" 点伤害，目前剩余血量：";color("Y");cout<<a[ffff].now_hp;color("W");cout<<"/";color("C");cout<<a[ffff].hp<<endl;color("W");

        }
        a[rushu+1].Tour_Skill=0;
    }
    else{
        int fff; 
        while (true){
             fff = rand ();
             if (fff % 3 != 2) break;
             else if (fff % 3 == 2 && doint1 == 0) break;
        }
        if (fff % 4 == 0){
            cout<<a[rushu+1].name<<"使用了-----";color("C");cout<<"神圣斩击";color("W");cout<<"-----(S级技能)!"<<endl;
            int shanghai=a[rushu+1].atk-a[j].ddf+rand()%50;
            a[rushu+1].Tour_Skill++;
            a[j].now_hp-=shanghai;voids();
            cout<<"玩家"<<a[j].name<<"受到了";color("R");cout<<shanghai;color("W");cout<<"点伤害，目前剩余血量：";cout<<a[j].now_hp;color("W");cout<<"/";color("C");cout<<a[j].hp<<endl;color("W");
        }
        else if (fff % 4 == 1){
            a [rushu+1].Tour_Skill ++;
            cout << a [rushu + 1].name << "使用了-----"; color ("Y"); cout << "剑刃风暴"; color ("W"); cout << "-----(S级技能)！" << endl;
            int aaa = 13 + (fff % 5);
            for (int i = 1;i <= aaa;i ++){
                Sleep (150); 
                int shanghai = 20 + rand ()% 10;
                while (true){
                    j = rand () % rushu + 1; if (a [j].now_hp > 0) break; 
                }
                cout << "玩家" << a [j].name << "受到了 " ; color ("R"); cout << shanghai ; color ("W"); cout << " 点伤害！" ;
                a [j].now_hp -= shanghai ; voids (); 
                cout << " 目前剩余血量：" ; color ("Y"); cout << a [j].now_hp ; color ("W"); cout << "/"; color ("C"); cout << a[j].now_hp; color ("W"); cout << endl; 
            } 
        }   
        else if (fff % 4 == 2){
            a [rushu+1].Tour_Skill ++;
            cout << a [rushu + 1].name << "使用了-----"; color ("B"); cout << "神圣剑阵" ; color ("W"); cout << "-----(S级技能)!" << endl ;
            cout << "生命值每回合回复 8%，持续3回合！" <<endl;
            Sleep (500);
            doint1 = 3;
        }
        else if (fff % 4 == 3){
            a [rushu + 1].Tour_Skill ++;
//            cout << 
        }
    }
} 

void dead(){
    for(int i=1;i<=rushu;i++){
        if(a[i].dead==false&&a[i].now_hp<=0)
            cout<<endl<<"玩家 "<<a[i].name<<" 阵亡！！！"<<endl;
            a[i].dead=true;
    }
}

void BOSS_skill7(int j){
    Sleep(500);
    if(a[rushu+1].Tour_Skill==4){
        cout<<a[rushu+1].name<<" 已经汲取了足够的雷神精华，使用神技了！！"<<endl;Sleep(500);
        for(j=1;j<=rushu;j++){
            if(a[j].now_hp<=0) continue;
            int shanghai=max(128,a[j].now_hp/2);a[j].now_hp-=shanghai;voids();
            cout<<a[j].name<<"受到了"<<shanghai<<"点伤害,目前剩余血量："; color("Y");cout<<a[j].now_hp;color("W");cout<<"/";color("C");cout<<a[j].hp<<endl;
        }
        a[rushu+1].Tour_Skill=0;
    } 
    else{
        int fff=rand()%10000;
        while(true){
            if(fff%5==0&&a[rushu+1].now_hp==a[rushu+1].hp) fff=rand()%10000;
            else break;
        }
        if(fff%5==0){
            cout<<a[rushu+1].name<<"使用了-----";color("B");cout<<"雷霆汲取";color("W");cout<<"-----(S级技能)！"<<endl;int get=min(500,(a[rushu+1].hp-a[rushu+1].now_hp)*3/10);
            cout<<a[rushu+1].name<<"恢复了已损失生命值的30%---(最多500)---";color("G");cout<<"---"<<get; color("W");cout<<"   ！！！"<<endl;Sleep(1200);
            cout<<"目前"<<a[rushu+1].name<<"剩余生命值为：";color("Y");cout<<"   "<<a[rushu+1].now_hp;color("W");cout<<"/";color("R");cout<<a[rushu+1].hp<<endl;color("W"); 
            a[rushu+1].Tour_Skill++;Sleep(500);color("C");
            cout<<endl<<a[rushu+1].name<<" 吸收了1点雷神精华，目前雷神精华:" <<a[rushu+1].Tour_Skill<<"  !!"<<endl;color("W"); 
        }
        else if(fff%5==1||fff%5==2){
            cout<<a[rushu+1].name<<"使用了-----";color("B");cout<<"雷霆一斩";color("W");cout<<"-----(S级技能)！"<<endl;
            int shanghai=a[rushu+1].atk/2+a[rushu+1].iq*3/4-a[j].ddf*3/2+rand()%30;
            cout<<a[j].name<<"受到了";
            color("R");cout<<shanghai;color("W");cout<<"点伤害！并且由于麻痹一回合停止行动！"<<endl;
            a[j].used=true;a[j].now_hp-=shanghai;voids();
            Sleep(500); a[rushu+1].Tour_Skill++;
            cout<<a[j].name<<"目前剩余血量:";cout<<"  ";color("Y");cout<<a[j].now_hp;color("W");cout<<"/";color("C");cout<<a[j].hp<<endl;color("W");
            Sleep(500);color("C");
            cout<<a[rushu+1].name<<" 吸收了1点雷神精华，目前雷神精华:" <<a[rushu+1].Tour_Skill<<"  !!"<<endl;color("W");  
        }
        else if(fff%5==3){
            cout<<a[rushu+1].name<<"使用了-----";color("B");cout<<"连锁雷电";color("W");cout<<"-----(S级技能)！"<<endl;
            for(int l=1;l<=3;l++){
                while(true){
                    j=rand()%rushu+1;
                    if(a[j].now_hp>0) break;
                } 
                Sleep(350); 
                int shanghai=a[rushu+1].iq-a[j].ddf*3/2+rand()%20;a[j].now_hp-=shanghai;voids();
                cout<<"玩家"<<a[j].name<<"受到了";color("R");cout<<shanghai;color("W");cout<<"点伤害!目前剩余血量： ";color("Y");cout<<a[j].now_hp;color("W");cout<<"/";color("C");cout<<a[j].hp<<endl;color("W");
            }
            a[rushu+1].Tour_Skill++;
            cout<<a[rushu+1].name<<" 吸收了1点雷神精华，目前雷神精华:" <<a[rushu+1].Tour_Skill<<"  !!"<<endl;color("W");  
        }
        else if(fff%5==4){
            cout<<a[rushu+1].name<<"使用了-----";color("B");cout<<"雷神制裁";color("W");cout<<"-----(S级技能)!"<<endl;
            cout<<"所有人获得了  ";color("Y");cout<<"麻痹  ";color("W");cout<<"状态，持续3回合！！！"<<endl;
            for(int i=1;i<=rushu;i++){
                if(a[i].now_hp>0)
                    a[i].ma_bi=3;
            }
            a[rushu+1].Tour_Skill++;
            cout<<a[rushu+1].name<<" 吸收了1点雷神精华，目前雷神精华:" <<a[rushu+1].Tour_Skill<<"  !!"<<endl;color("W");  
        }
    }
}

void peoples(){
    Slowsay("请输入挑战BOSS的人数\n");cin>>rushu;
        for(int i=1;i<=rushu;i++){
            Slowsay("请输入玩家");cout<<i;Slowsay("的名字！\n");
            cin>>a[i].name;
            if(check(i)==false){
                while(true){Slowsay("名字重复！请重新输入玩家");cout<<i;Slowsay("的名字！\n");cin>>a[i].name;if(check(i)==true) break;else continue;}
            }   
        }
}

bool check2(){
    for(int i=1;i<=rushu;i++)
        if(a[i].now_hp>0)
            return false;
    return true;
}

void BOSS(int p){
    if(p==1){
        a[rushu+1].name="萨满";a[rushu+1].atk=200;a[rushu+1].ddf=120;a[rushu+1].iq=200;a[rushu+1].hp=1000;a[rushu+1].now_hp=1000;a[rushu+1].su=10;
    }else if(p==2){
        a[rushu+1].name="帝君肉山";a[rushu+1].atk=120;a[rushu+1].ddf=155;a[rushu+1].iq=30;a[rushu+1].hp=2500;a[rushu+1].now_hp=2500;a[rushu+1].su=10;
    }else if(p==3){
        a[rushu+1].name="邪神satan";a[rushu+1].atk=300;a[rushu+1].ddf=65;a[rushu+1].iq=325;a[rushu+1].hp=1000;a[rushu+1].now_hp=1000;a[rushu+1].su=10;
    }else if(p==7){
        a[rushu+1].name="雷神Tour";a[rushu+1].atk=250;a[rushu+1].ddf=108;a[rushu+1].iq=250;a[rushu+1].hp=3000;a[rushu+1].now_hp=3000;a[rushu+1].su=10;a[rushu+1].BOSs=7;
    }else if(p==8){
        a[rushu+1].name="圣骑剑圣";a[rushu+1].atk=300;a[rushu+1].ddf=85;a[rushu+1].iq=20;a[rushu+1].hp=3500;a[rushu+1].now_hp=3500;a[rushu+1].su=10;a[rushu+1].BOSs=8;
    } 
}

void moshi2_boss(){
    int choosex,choosep;
    Slowsay("欢迎来到挑战BOSS模式！在这里你会感受到被虐带来的无上快感！\n请选择BOSS难度\n");
    while(true){
        Slowsay("(1) 简单难度\n(2) 挑战难度\n(3) 困难难度\n(4) 噩梦难度\n");
        cin>>choosex;
        if(choosex==1||choosex==2||choosex==3||choosex==4) break;
        system("cls");
    }
    if(choosex==1){
        system("cls");
        Slowsay("您选择了[普通难度]！！\n");
        Sleep(500);
        peoples();
        Slowsay("\n请选择你想要挑战的BOSS\n");
        Slowsay("(1) 萨满\n(2) 帝君肉山\n(3) 邪神Satan\n");
        cin>>choosep;
        if(choosep==1) BOSS(1);
        else if(choosep==2) BOSS(2);
        else if(choosep==3) BOSS(3);
    }
    else if(choosex==2){
        system("cls");
        Slowsay("您选择了[挑战难度]！！\n");
        Sleep(500);
        peoples();
        Slowsay("\n请选择你想要挑战的BOSS\n");
        Slowsay("(1) 鬼牙\n(2) 紫金守卫\n(3) 地狱龙\n");
        cin>>choosep;
        if(choosep==1) BOSS(4);
        else if(choosep==2) BOSS(5);
        else if(choosep==3) BOSS(6);
    }
    else if(choosex==3){
        system("cls");
        Slowsay("您选择了[困难难度]！！\n");
        Sleep(500);
        peoples();
        Slowsay("\n请选择你想要挑战的BOSS\n");
        Slowsay("(1) 雷神Tour\n(2) 圣骑剑圣\n(3) 紫金执法者\n");
        cin>>choosep;
        if(choosep==1) BOSS(7);
        else if(choosep==2) BOSS(8);
        else if(choosep==3) BOSS(9);
    }
    for(int i=1;i<=rushu;i++){
            a[i].atk=rand()%50+70;
            a[i].ddf=rand()%30+50;
            a[i].hp=rand()%200+500;
            a[i].su=rand()%10+1;
            a[i].iq=rand()%40+70;
            a[i].zhan=a[i].atk*16+a[i].ddf*18+a[i].hp*3+a[i].su*5+a[i].iq*15;
            a[i].now_hp=a[i].hp;
        }
    for(int i=1;i<=rushu;i++) zhandui(i);
    for(int i=1;i<=rushu;i++){
        if(a[i].zd==0) continue;
        else zhandui_xun(i);
    }
    for(int i=1;i<=rushu;i++) a[i].zhan=a[i].atk*16+a[i].ddf*18+a[i].hp*3+a[i].su*5+a[i].iq*15;
    a[rushu+1].zhan=a[rushu+1].atk*16+a[rushu+1].ddf*18+a[rushu+1].hp*3+a[rushu+1].su*5+a[rushu+1].iq*15;
    for(int i=1;i<=rushu+1;i++){
        Sleep(500);
        cout<<endl;
        if(i==rushu+1){
            cout<<"BOOS-----"<<a[i].name<<" 接受了挑战！属性为："<<endl;Sleep(500); 
            cout<<"攻击:"<<a[i].atk<<"  护甲:"<<a[i].ddf<<"  体力:"<<a[i].hp<<"  速度:"<<a[i].su<<"  智力:"<<a[i].iq<<endl;Sleep(500);
            cout<<a[i].name<<"战斗力为:"<<a[i].zhan;
            cout<<endl;
            break;
        } 
        cout<<"玩家"<<i<<"的名字是："<<a[i].name<<endl;Sleep(500);
        cout<<"攻击:"<<a[i].atk<<"  护甲:"<<a[i].ddf<<"  体力:"<<a[i].hp<<"  速度:"<<a[i].su<<"  智力:"<<a[i].iq<<endl;Sleep(500);
        cout<<a[i].name<<"战斗力为:"<<a[i].zhan;
        cout<<endl;
    }
    cout<<"\n\n";
    Slowsay("\n输入1继续。。。\n");int u;cin>>u;
    if(u==2) rushu++; 
    cout<<"出招顺序\n";
    for(int i=1;i<=rushu;i++){
        cout<<"No."<<i<<" "<<a[i].name<<"\n";
    }int j,k=0;
    system("cls");
    cout<<endl<<"----人神共愤"<<endl;
    Sleep(500);
    cout<<"                     天诛地灭----"<<endl;
    Sleep(500);
    cout<<"战斗开始—————————————！！！"<<endl; Sleep(500); 
    while(true){
        for(int i=1;i<=rushu+1;i++){
            if(a[i].used==true){a[i].used=false;continue;}
            if(a[i].ma_bi>0){
                a[i].ma_bi--;a[i].now_hp-=50;voids();
                cout<<endl<<"玩家"<<a[i].name<<"处于 麻痹 状态，收到了";color("B");cout<<50;color("W");cout<<" 点伤害！目前剩余血量：";color("Y");cout<<a[i].now_hp;color("W");cout<<"/";color("C");cout<<a[i].hp<<endl<<endl;color("W");
            }
            if (i == rushu +1 && doint1 > 0){
                Sleep (250);
                cout << endl;
                int shanghai = (int) a [rushu + 1].hp * 0.08;a [rushu + 1].now_hp += shanghai ; voids ();
                cout << a [rushu + 1].name << "恢复了" ; color ("G"); cout << shanghai; color ("W"); cout << " 点生命值!  目前剩余生命值：" ; color ("Y"); cout << a [rushu + 1].now_hp ; color ("W"); cout << "/"; color ("C"); cout << a [rushu + 1].hp ; color ("W");
                doint1 --; 
                cout << endl;
            }
            if(a[i].now_hp<=0) continue;
            cout<<endl;
            if(i!=rushu+1) j=rushu+1;
            else if(i==rushu+1){
                while(true){j=rand()%rushu+1;if(a[j].now_hp>0) break;}
            }
            int fff=rand()%12000;
            if(a[rushu+1].now_hp<=0){k=1;break;}
            else if(check2()==true){k=1;break;}
            if(i==rushu+1&&a[i].BOSs==7) BOSS_skill7(j);
            else if(i==rushu+1&&a[i].BOSs==8) BOSS_skill8(j);
            else{
                while(true){
                    if(fff%10==4&&a[i].atk_used==true) fff=rand()%12000;
                    else if(fff%10==5&&a[i].ddf_used==true) fff=rand()%12000;
                    else if((fff%10==8||fff%10==9)&&a[i].now_hp==a[i].hp) fff=rand()%12000;
                    else break;
                }
                if(fff%10==1) pugong(i,j);
                if(fff%10==0) xiaolifeidao(i,j);
                else if(fff%10==2) huoqiushu(i,j);
                else if(fff%10==3) leijishu(i,j);
                else if(fff%10==4) kuangbao(i);
                else if(fff%10==5) tiebishu(i);
                //else if(fff%10==6) bingdongshu(i,j);
                else if(fff%10==7||fff%10==6) changqiongzhan(i,j);
                else if(fff%10==8) huifushu(i);
                else if(fff%10==9) shixueyiji(i,j);
            }
            cout<<endl;
            dead();
        }
        if(a[rushu+1].now_hp<=0||check2()==true) break;
    }
    Slowsay("-----战斗结束！！！-----\n");
    if(a[rushu+1].now_hp<=0) Slowsay("玩家们获胜!\n");
    else if(check2()==true) Slowsay("BOSS获胜!\n");
}

bool comp2(people x,people y){
    return x.score>y.score;}

void voids (){
    for(int i=1;i<=rushu+1;i++){
        if(a[i].now_hp>=a[i].hp) a[i].now_hp=a[i].hp;
        else if(a[i].now_hp<=0) a[i].now_hp=0;
    }
}

bool panduan(){
    int f=0;
    for(int i=1;i<=rushu;i++)
        if(a[i].now_hp<=0)
            f++;
    if(f==rushu-1) return true;
    else return false;
}

bool comp(people x, people y){
return x.su>y.su;}

bool check(int i){
    if(i==1) return true; 
    for(int s=1;s<=i-1;s++){
        if(a[s].name == a[i].name)
            return false;
    } 
    return true;
}

void moshi1(void){
    Slowsay("请输入玩家人数（2~10001）\n");
    cin>>rushu;
    for(int i=1;i<=rushu;i++){
        Slowsay("请输入玩家");cout<<i;Slowsay("的名字！\n");
        cin>>a[i].name;
        if(check(i)==false){
            while(true){Slowsay("名字重复！请重新输入玩家");cout<<i;Slowsay("的名字！\n");cin>>a[i].name;if(check(i)==true) break;else continue;}
        }   
    }
    for(int i=1;i<=rushu;i++){
        a[i].atk=rand()%50+70;
        a[i].ddf=rand()%30+50;
        a[i].hp=rand()%200+400;
        a[i].su=rand()%10+1;
        a[i].iq=rand()%40+70;
        a[i].zhan=a[i].atk*16+a[i].ddf*18+a[i].hp*3+a[i].su*5+a[i].iq*15;
        a[i].now_hp=a[i].hp;
    }
    for(int i=1;i<=rushu;i++){
        Sleep(500);
        cout<<endl;
        cout<<"玩家"<<i<<"的名字是："<<a[i].name<<endl;Sleep(500);
        cout<<"攻击:"<<a[i].atk<<"  护甲:"<<a[i].ddf<<"  体力:"<<a[i].hp<<"  速度:"<<a[i].su<<"  智力:"<<a[i].iq<<endl;Sleep(500);
        cout<<a[i].name<<"战斗力为:"<<a[i].zhan;
        cout<<endl;
    }
    zhandui(1);zhandui(2);
    for(int i=1;i<=rushu;i++){
        if(a[i].zd==0) continue;
        else zhandui_xun(i);
    }
    cout<<"\n\n";
    Slowsay("输入1继续，输入0退出\n");
    cin>>choose1;
    if(choose1==0) cout<<"结束!!"<<endl;
    else{
        system("cls");
        cout<<"即将开始，请等待3秒。。。"<<endl;
        Sleep(500); cout<<"3......"<<endl;
        Sleep(500); cout<<"2......"<<endl;
        Sleep(500); cout<<"1......"<<endl;
        cout<<"开始!!"<<endl<<endl<<endl;
    }
    int max_su=0;
    for(int i=1;i<=rushu;i++) max_su=max(max_su,a[i].su);
    sort(a+1,a+rushu+1,comp);
    cout<<"出招顺序\n";
    for(int i=1;i<=rushu;i++){
        cout<<"No."<<i<<" "<<a[i].name<<"\n";
    }
    int ko=rand()%rushu+1;
    Sleep(500);
    cout<<endl<<endl<<a[ko].name<<"本局收到了神圣祝福！全属性加10%!"<<endl;
    a[ko].atk+=a[ko].atk/10;
    a[ko].ddf+=a[ko].ddf/10;
    a[ko].hp+=a[ko].hp/10;
    a[ko].iq+=a[ko].iq/10;
    a[ko].now_hp=a[ko].hp;
    system("cls");
    cout<<endl<<"----人神共愤"<<endl;
    Sleep(500);
    cout<<"                     天诛地灭----"<<endl;
    Sleep(500);
    cout<<"战斗开始——————————————！！！"<<endl; 
    //system("cls");
    Sleep(500);
    int pko=0;
    while(panduan()==false){
        for(int i=1;i<=rushu;i++){
            if(a[i].used==true){a[i].used=false;continue;}
            if(a[i].now_hp<=0) continue;
            cout<<endl<<endl;
            int fff=rand(),j;
            while(true){j=rand()%rushu+1;if(j!=i&&a[j].now_hp>0) break;}
            //cout<<fff<<endl;
            while(true){
                if(fff%10==4&&a[i].atk_used==true) fff=rand()%12000;
                else if(fff%10==5&&a[i].ddf_used==true) fff=rand()%12000;
                else if((fff%10==8||fff%10==9)&&a[i].now_hp==a[i].hp) fff=rand()%12000;
                else break;
            }
            if(fff%10==1) pugong(i,j);
            if(fff%10==0) xiaolifeidao(i,j);
            else if(fff%10==2) huoqiushu(i,j);
            else if(fff%10==3) leijishu(i,j);
            else if(fff%10==4) kuangbao(i);
            else if(fff%10==5) tiebishu(i);
            else if(fff%10==6) bingdongshu(i,j);
            else if(fff%10==7) changqiongzhan(i,j);
            else if(fff%10==8) huifushu(i);
            else if(fff%10==9) shixueyiji(i,j);
            cout<<endl;
            if(panduan()==true){
                Sleep(500); 
                cout<<"\n\n";
                cout<<"战斗结束！"<<endl;
                Slowsay("------------------得分表-------------------\n");int kol;
                for(int f=1;f<=rushu;f++)
                    if(a[f].now_hp>0) kol=f;
                Slowsay("获胜者-------");cout<<a[kol].name<<"!!!  得分："<<a[kol].score<<"\n";
                Slowsay("-------------------------------------------\n"); Sleep(500);
                sort(a+1,a+1+rushu,comp2);
                for(int f=1;f<=rushu;f++){
                        Sleep(250);
                        cout<<"名字："<<a[f].name<<"   得分："<<a[f].score<<endl; 
                }
            }
        }   
    }
    /*for(int i=1;i<=rushu;i++){
        a[i].zhan=a[i].atk*16+a[i].ddf*18+a[i].hp*3+a[i].su*5+a[i].iq*15;
        Sleep(500);
        cout<<endl;
        cout<<"玩家"<<i<<"的名字是："<<a[i].name<<endl;
        cout<<"攻击:"<<a[i].atk<<"  护甲:"<<a[i].ddf<<"  体力:"<<a[i].hp<<"  速度:"<<a[i].su<<"  智力:"<<a[i].iq<<endl;
        cout<<a[i].name<<"战斗力为:"<<a[i].zhan;
        cout<<endl;
    }*/
    Slowsay("\n输入1继续。。。");int pop;cin>>pop;
    system("cls");
    moshi1();
}

void Slowsay(string s){
    for(int i=0;s[i];i++){
        cout<<s[i];
        Sleep(10);
    }
}

void shixueyiji(int i,int j){
    Sleep(500);
    int shanghai=a[i].atk*3/2+rand()%15;
    shanghai-=a[j].ddf*2/3;
    if(shanghai<=40) shanghai=40+rand()%15;
    cout<<a[i].name<<" 使用了-----";color("Y");cout<<"嗜血一击";color("W");cout<<"-----(A级技能)"<<endl;
    a[j].now_hp-=shanghai;
    a[i].now_hp+=shanghai/2;
    Sleep(500);
    cout<<a[j].name<<"　受到攻击，被造成了";color("R");cout<<shanghai<<endl;color("W");
    cout<<a[i].name<<" 嗜血！ 恢复了";color("G");cout<<shanghai/2<<endl;color("W");
    Sleep(450);cout<<"目前两人剩余血量-----    ";voids();
    color("G");cout<<a[i].now_hp;color("W");cout<<"/"<<" ";color("Y");cout<<a[i].hp;color("W"); 
    color("G");cout<<a[j].now_hp;color("W");cout<<"/"<<" ";color("Y");cout<<a[j].hp;color("W");
    a[i].score+=shanghai*3/2;
    a[j].score+=shanghai/3;
}

void huifushu(int i){
    Sleep(500);
    int shanghai=a[i].iq+a[i].atk/2;
    cout<<a[i].name<<"使用了-----";color("B");cout<<"恢复术";color("W");cout<<"-----(B级技能)"<<endl;
    a[i].now_hp+=shanghai;
    Sleep(900);
    cout<<"恢复了";color("G");cout<<shanghai;color("W");cout<<"　点血量!";voids();
    cout<<"目前"<<a[i].name<<"剩余血量-----    ";color("G");cout<<a[i].now_hp;color("W");cout<<"/";color("Y");cout<<a[i].hp;color("W");
    a[i].score+=shanghai;
}

void changqiongzhan(int i,int j){
    Sleep(500);
    cout<<"-----";
    color("R");cout<<"神技降临";color("W");cout<<"-----"<<endl; 
    Sleep(500);
    color("Y"); cout<<"-万-"<<endl;Sleep(500);
    color("G"); cout<<"-劫-"<<endl;Sleep(500);
    color("B"); cout<<"-不-"<<endl;Sleep(500);
    color("C") ;cout<<"-复-"<<endl;Sleep(500);
    int shanghai=a[i].atk+a[i].iq+rand()%20;
    cout<<a[i].name<<" 使用了-----";
    color("Y");cout<<"苍穹斩！";color("W");cout<<"-----";color("R");cout<<"(神级技能)";color("W");cout<<"-----\n"; 
    Sleep(800);
    color("Y");cout<<"流星赶月，神之一斩，撕裂苍穹！"<<endl;color("W");
    Sleep(580);
    shanghai-=a[j].ddf;
    if(shanghai<=50) shanghai=50+rand()%20;
    a[j].now_hp-=shanghai;
    cout<<a[j].name<<"　受到了";
    color("R");cout<<shanghai;color("W");
    cout<<" 点伤害！--------" <<endl;voids();
    cout<<"目前 "<<a[j].name<<"　剩余血量-----";cout<<a[j].now_hp;color("W");cout<<"/"<<" ";color("Y");cout<<a[j].hp;color("W");
    a[i].score+=shanghai;
    a[j].score+=shanghai/3;
} 

void zhandui(int i){
    if(a[i].name=="xiongxingzhuang"){a[i].zd=1;}
    else if(a[i].name=="lizewen"){a[i].zd=2;} 
    else if(a[i].name=="maozedong"||a[i].name=="李大钊同志"||a[i].name=="陈独秀同志"){a[i].zd=3;}
    else if(a[i].name=="satan") a[i].zd=4;
    else if(a[i].name=="god_down") a[i].zd=5;
    else if(a[i].name=="power") a[i].zd=6;
    else if(a[i].name=="zengchiye") a[i].zd=7;
    else if(a[i].name=="bangbangchui") a[i].zd=8;
} 

void zhandui_xun(int i){
    color("R");
    Sleep(500);
    cout<<endl;
    cout<<"触发隐藏战队___系统！！！"<<endl;color("W");
    Sleep(500);
    for(int j=1;j<=100;j++){
        if(a[i].zd==j){
            zhandui_xun2(j,i);
            break;
        }
    }
}

void zhandui_xun2(int j,int i){
    cout<<a[i].name<<"   ----    ";
    if(j==1){color("R");cout<<"priority_queue_战队";} 
    else if(j==2){color("BULE");cout<<"Sir_战队";}
    else if(j==3){color("Y");cout<<"革命之星_战队";}
    else if(j==4){color("R");cout<<"死神联盟_SSRPOWER(BOSS集团)";}
    else if(j==5){color("R");cout<<"死神联盟_SSRPOWER(BOSS集团)";}
    else if(j==6){color("C");cout<<"无上神域__圣堂(BOSS集团)";}
    else if(j==7){color("Y");cout<<"神王&降临";}
    else if(j==8){color("Y");cout<<"神王&降临";}
    color("W");
    Sleep(500);
    cout<<"-----"<<endl;
    Sleep(500);
    cout<<"战队特殊技能  ： ";
    if(j==1){color("C");cout<<"先发制人-----效果:优先出手一次"<<endl;a[i].su+=10;a[i].atk+=120;a[i].iq+=120;a[i].now_hp+=2000;a[i].hp+=2000;a[i].ddf+=50;} 
    else if(j==2){color("B");cout<<"绅士的力量-----效果:开局咸猪手(攻击力增加)"<<endl;a[i].atk+=15;}
    else if(j==3){color("B");cout<<"农村的力量-----效果:生命上限增加"<<endl;a[i].hp+=80;a[i].now_hp+=80;}
    else if(j==4){color("R");cout<<"BUG_BOSS_无法战胜！！----效果：全属性增加！"<<endl;a[i].now_hp+=1200;a[i].iq+=45;a[i].atk+=40;a[i].su+=5;a[i].ddf+=10;a[i].hp+=1200;}
    else if(j==5){color("R");cout<<"堕落--神圣祝福-- ^^^　效果：攻击力增加，全属性降低"<<endl;a[i].atk=a[i].atk*3;a[i].ddf-=5;a[i].now_hp+=200;a[i].su+=10;a[i].iq+=120;a[i].hp+=200;}
    else if(j==6){color("B");cout<<"无上神域-----效果：生命上限增加，防御力增加"<<endl;a[i].hp+=1500;a[i].now_hp+=1500;a[i].ddf+=100;a[i].iq+=20;}
    else if(j==7){color("G");cout<<"上";color("R");cout<<"位";color("Y");cout<<"威";color("C");cout<<"压";color("B");cout<<"-----效果：全属性大幅度增强";
                 a[i].hp+=12000;a[i].now_hp+=5000;a[i].atk+=2600;a[i].iq+=3000;a[i].ddf+=1000;a[i].su+=100;}
    else if(j==8){color("G");cout<<"上";color("R");cout<<"位";color("Y");cout<<"威";color("C");cout<<"压";color("B");cout<<"-----效果：全属性大幅度增强";
                 a[i].hp+=30000;a[i].now_hp+=30000;a[i].atk+=1000;a[i].iq+=1000;a[i].ddf+=3000;}
    color("W");
    cout<<endl;
}

void color(string i){
    if(i=="B")SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
    else if(i=="W")SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    else if(i=="R")SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
    else if(i=="Y")SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
    else if(i=="G")SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
    else if(i=="C")SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
    //else if(i=="MAGENTA");SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_R | FOREGROUND_B);
}

void bingdongshu(int i,int j){
    Sleep(500);
    int shanghai=a[i].iq+rand()%10;
    shanghai-=a[j].ddf*5/4;
    if(shanghai<=20) shanghai=20+rand()%10;
    a[j].now_hp-=shanghai;
    cout<<a[i].name<<" 使用了----";
    color("B");cout<<"冰封万里";color("W");
    cout<<"----（A级技能）"<<endl;
    a[j].used=true;
    Sleep(500);
    cout<<a[j].name<<" 被魔法力量冰冻了，下回合无法行动！"<<endl;
    Sleep(500);
    cout<<"同时受到了";
    color("R"); cout<<shanghai;color("W");
    cout<<" 点";voids();
    color("G");cout<<"魔法伤害";color("W");cout<<endl;cout<<"目前"<<a[j].name<<"剩余血量----"; 
    cout<<a[j].now_hp;color("W");cout<<"/"<<" ";color("Y");cout<<a[j].hp;color("W");
    a[i].score+=shanghai*3/2;
}

void tiebishu(int i){
    Sleep(500);
    int get_atk=a[i].iq/5+rand()%10;
    a[i].ddf+=get_atk;
    cout<<a[i].name<<" 使用了----";
    color("B");cout<<"铁壁术";color("W");
    cout<<"----（B级技能）"<<endl;
    Sleep(500);
    cout<<a[i].name<<" 防御力上升";
    color("R");cout<<get_atk;color("W");
    cout<<" 点！目前防御力："<<a[i].ddf<<endl;
    a[i].score+=get_atk*2;
    a[i].ddf_used=true;
}

void kuangbao(int i){
    Sleep(500);
    int get_atk=a[i].iq/3+rand()%10;
    a[i].atk+=get_atk;
    a[i].iq+=get_atk/3;
    cout<<a[i].name<<" 使用了----";
    color("B");cout<<"狂暴术";color("W");
    cout<<"----（B级技能）"<<endl;
    cout<<a[i].name<<" 攻击力上升";
    color("R");cout<<get_atk;color("W");
    cout<<" 点！目前攻击力："<<a[i].atk<<endl;
    a[i].score+=get_atk*2;
    a[i].atk_used=true;
}

void leijishu(int i,int j){
    Sleep(500);
    int shanghai=a[i].iq*3/8;
    int nice=rand()%4+3;
    int resthp=0;
    cout<<a[i].name<<" 使用了----";
    color("Y");cout<<"雷击术";color("W");
    cout<<"----（A级技能)！"<<endl;
    for(int p=1;p<=nice;p++){
        Sleep(500);
        for(int f=1;f<=p;f++) cout<<" ";
        int lo=shanghai-a[j].ddf/4+rand()%10;
        if(lo<=10) lo=10+rand()%10;
        a[j].now_hp-=lo;
        resthp+=lo;
        cout<<a[i].name<<" 对 "<<a[j].name<<"　造成了　";
        color("R");cout<<lo;color("W");
        cout<<"点伤害！"<<endl;
        if(p==nice){
            Sleep(500);
            cout<<"共造成";voids();
            color("R");cout<<resthp;color("W");
            cout<<" 点伤害\n";
            cout<<a[j].name<<" 剩余血量-----";cout<<a[j].now_hp;color("W");cout<<"/"<<" ";color("Y");cout<<a[j].hp;color("W");
            a[i].score+=resthp*4/3;
            a[j].score+=resthp/3;
        }
    }
}

void huoqiushu(int i,int j){
    Sleep(500);
    int num=rand()%100+50;
    int shanghai=a[i].atk*9/5;
    shanghai-=a[j].ddf;
    if(shanghai<=40) shanghai=40+rand()%5;
    a[j].now_hp-=shanghai;
    cout<<a[i].name<<"使用了-----";
    color("R");cout<<"实力秒杀！！";color("W");
    cout<<"（S级技能）------"<<endl;
    Sleep(500); 
    cout<<a[j].name<<"受到了";
    color("R");cout<<shanghai;color("W");
    cout<<"点伤害！\n"<<endl;voids();
    cout<<a[j].name<<" 目前剩余血量-----";cout<<a[j].now_hp;color("W");cout<<"/"<<" ";color("Y");cout<<a[j].hp;color("W");
    a[i].score+=shanghai;
    a[j].score+=shanghai/3;
}

void pugong(int i,int j){
    Sleep(500); 
    int num=rand()%15+5;
    int shanghai=num+a[i].atk;
    if(shanghai<a[j].ddf+15) shanghai=a[j].ddf+15;
    int lose=shanghai-a[j].ddf;
    a[j].now_hp-=lose;voids();
    cout<<a[j].name<<"受到了来自  玩家"<<a[i].name<<"的攻击！"<<endl;
    cout<<"--------------造成了"<<lose<<"点伤害\n目前"<<a[i].name<<"剩余血量-----";cout<<a[j].now_hp;color("W");cout<<"/"<<" ";color("Y");cout<<a[j].hp;color("W");
    a[i].score+=lose;
    a[j].score+=lose/3;
}

void xiaolifeidao(int i,int j){
    Sleep(500);
    int num=rand()%100+65,get;
    int shanghai;
    shanghai=a[i].atk*5/12-a[j].ddf*5/4+a[i].iq+num/8;
    if(shanghai<=20) shanghai=20+rand()%3;
    a[j].now_hp-=shanghai;
    cout<<a[i].name<<" 摸摸口袋，掏出一把匕首———";
    Sleep(500);
    cout<<"天下秘籍,--------";
    color("G");cout<<"小李飞刀";color("W");
    cout<<"---------！！（C级技能）"<<endl;
    Sleep(500);
    cout<<a[i].name<<"将匕首朝着 "<<a[j].name<<" 丢了过去，造成了" ;
    color("R");cout<<shanghai;color("W");
    cout<<"点伤害\n"<<endl;voids();
    cout<<"目前 "<<a[j].name<<" 剩余血量-----";cout<<a[j].now_hp;color("W");cout<<"/"<<" ";color("Y");cout<<a[j].hp;color("W");
    a[i].score+=shanghai*3/2;
    a[j].score+=shanghai/2;
    Sleep(500);
    if(num%2==1){
        cout<<"--------还没完！  "<<a[i].name<<" 的--小李飞刀--（C级技能）连击！"<<endl;
         a[j].now_hp-=shanghai/2;voids();
         cout<<"--------------造成了"<<shanghai/2<<"点伤害\n目前"<<a[j].name<<"剩余血量-----"<< a[j].now_hp<<"/"<< a[j].hp<<endl;
    }
}

int main(){
    system("cls");
    srand(time(0));
    color("W");
    Slowsay("欢迎来到名字大作战！    -----作者：曾哥\n");Sleep(500);
    Slowsay("请选择......\n");Sleep(500);
    while(true){
        na:;
        Slowsay("(1) 开始游戏\n(2) 查看更新日志\n(3) 设置\n(4) 游戏相关\n");
        cin>>choose1;
        if(choose1==1||choose1==2||choose1==3||choose1==4) break;
        else system("cls");
    }
    if(choose1==1){
        system("cls");
        Slowsay("----------请选择游戏模式----------\n");
        while(true){
        Slowsay("(1)  玩家对战模式\n(2)  挑战BOSS模式 \n(3)  [高难度]挑战系统团队模式 \n(4)  闯关模式(开发中) \n(5)  返回主界面\n");
        cin>>choose2;if(choose2>=1&&choose2<=5) break;else system("cls");
        }
        if(choose2==5){system("cls");goto na;}
        else if(choose2==1){system("cls");moshi1();}
        else if(choose2==2){system("cls");moshi2_boss();}
    }
    else if (choose1 == 2){
        write1 ();
    }
}
