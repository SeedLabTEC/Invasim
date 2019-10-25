int main()
{
        int sum = 0;
        int i;

        for (i = 0; i < 1000000000; i++)
        {
                //prg from
                sum = (sum + 7) * 5;
                sum = (sum + 11) * 9;
                sum = (sum + 13) * 12;
                //prg to
                sum = (sum + 17) * 15;
                sum = (sum + 19) * 18;
                sum = (sum + 23) * 20;
                sum = (sum + 29) * 25;
                sum = (sum + 31) * 27;
        }
        return sum;
}