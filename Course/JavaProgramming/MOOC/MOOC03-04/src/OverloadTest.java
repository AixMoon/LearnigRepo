
public class OverloadTest {

	public static void main(String[] args) {
		int a=1,b=2;
		System.out.println(add(1,2));
		System.out.println(add(1.5,2.5));
	}

	public static int add(int m, int n) 
	{
		return m + n;
	}
	public static double add(double m, double n) //�͵�9����������overload
	{
		return m + n;
	}
	/*
	 * ���º����Ƿ����͵�9�еĺ�������ͬ���β���ͬ
	public static double add(int m, int n) 
	{
		return (double) (m + n);
	}
	*/
}
