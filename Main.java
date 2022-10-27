import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String input = sc.nextLine();
        String[] data = input.split(" ");

        boolean neg1 = data[0].charAt(0) == '-',
                neg2 = data[2].charAt(0) == '-';

        int[] f1 = str2frac(data[0]);
        int[] f2 = str2frac(data[2]);

        f1[1] += f1[0] * f1[2];
        f2[1] += f2[0] * f2[2];
        if (neg1) f1[1] *= -1;
        if (neg2) f2[1] *= -1;

        display(simplify(calculate(f1, f2, data[1].charAt(0))));
    }

    static int[] str2frac(String s) {
        if (s.charAt(0) == '-') s = s.substring(1, s.length());
        int[] frac = new int[3];

        int i = s.indexOf("_");
        if (i != -1)
        {
            frac[0] = Integer.parseInt(s.substring(0, i));
            s = s.substring(i + 1, s.length());
        }

        i = s.indexOf("/");

        if (i != -1)
        {
            frac[1] = Integer.parseInt(s.substring(0, i));
            frac[2] = Integer.parseInt(s.substring(i + 1, s.length()));
        }
        else
        {
            frac[1] = Integer.parseInt(s);
            frac[2] = 1;
        }

        return frac;
    }

    static int[] calculate(int[] f1, int[] f2, char op) {
        int[] res = new int[2];

        if (op == '+' || op == '-')
        {
            f1[1] *= f2[2];
            f2[1] *= f1[2];

            float tmp = f1[2];
            f1[2] *= f2[2];
            f2[2] *= tmp;

            res[1] = f1[2];
            if (op == '+') res[0] = f1[1] + f2[1];
            else           res[0] = f1[1] - f2[1];
        }

        if (op == '*')
        {
            res[0] = f1[1] * f2[1];
            res[1] = f1[2] * f2[2];
        }

        if (op == '/')
        {
            res[0] = f1[1] * f2[2];
            res[1] = f1[2] * f2[1];
        }

        return res;
    }

    static int[] simplify(int[] res) {
        int gcf = 1;

        for (int i = 1; i <= Math.min(Math.abs(res[0]), Math.abs(res[1])); ++i) {
            if (res[0] % i == 0 && res[1] % i == 0)
                gcf = i;
        }

        res = new int[]{ res[0] / gcf, res[1] / gcf };
        return res;
    }

    static void display(int[] res) {
        int sign = Integer.signum(res[0]) * Integer.signum(res[1]);
        int whole = res[0] / res[1];
        res[1] = Math.abs(res[1]);
        res[0] = Math.abs(res[0] % res[1]);

        if (res[0] % res[1] == 0 && whole == 0)
        {
            System.out.println("0");
        }
        else
        {
            if (whole != 0) System.out.print(whole);
            else System.out.print(sign > 0 ? "" : "-");

            if (res[0] % res[1] != 0 && whole != 0)
            {
                System.out.print("_");
                System.out.print(res[0] % res[1]);
                System.out.print("/");
                System.out.print(res[1]);
            }

            System.out.println("");
        }
    }
}