
public class Student {
	
	public int divide(int x, int y) 
	{
		return x/y;
	}
	
	public static void main(String[] args) throws DivideByMinusException{
		Student newton = new Student();
		//newton.divide2(5, 0);
		newton.divide5(5, -2);
	}	
	
	public int divide2(int x, int y)
	{
		int result;
		try
		{
			result = x/y;
			System.out.println("result is " + result);
		}
		catch(ArithmeticException ex)
		{
			System.out.println(ex.getMessage());
			return 0;
		}
		catch(Exception ex)
		{
			ex.printStackTrace();
			return 0;
		}
		return result;
	}
	
	//ArithmeticException is a unchecked exception,���������Բ���
	public int divide3(int x, int y) throws ArithmeticException
	{		
		return x/y;
	}
	
	public int divide4(int x, int y) 
	{		
//		try
//		{
//			return divide3(x,y);
//		}
//		catch(ArithmeticException ex)
//		{
//			ex.printStackTrace();
//			return 0;
//		}
		return divide3(x,y);  //����divide3�����쳣��divide4���账����Ϊ����쳣��unchecked exception
		//�������divide5(x,y);  ��ô����Ҫ��try������catch������Ϊ���׳�checked exception
	}
	
	public int divide5(int x, int y) throws DivideByMinusException
	{		
		try
		{
			if(y<0)
			{
				throw new DivideByMinusException("The divisor is negative", y);
			}
			return divide3(x,y);
		}
		catch(ArithmeticException ex)
		{
			ex.printStackTrace();
			return 0;
		}
	}
}
