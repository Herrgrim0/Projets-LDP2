/* Langages de programmation 2 - Projet java
 * GRIMAU Romain
 * 000440048
 * 16/08/2018
 */

import java.util.Arrays; // copyOf(), toString(),...

public class Vect0<T extends Number> {
	/*encapsulate a basic type array and
	 * handle the cut in x subarray and the launch
	 * of 2 methods in multi-threading*/
	private static int MAXTHREAD = 100;
	private int lenThreadVect;
	private T[] vect;
	private int len;
	private int nbrthread;
	private T product;

	@SuppressWarnings("unchecked")
	public Vect0(T[] vector){
		this.len = vector.length;
		this.vect = Arrays.copyOf(vector, this.len);
		this.setNbrThread();
		this.product = (T)(Integer)0;
	}

	public void CalculScalProd(Vect0<T> Other){
		/*Launch scalar product in multi-threading*/
		int start, stop;
		Thread t[] = new Thread[this.nbrthread];
		for(int i = 0; i<nbrthread;i++){
			if (nbrthread == 1) {
				t[i] = new Thread(new ThreadScalProd<>(this, Other, 0, this.len));
				t[i].start();
			}
			else if (nbrthread == 2) {
				start = i*this.len/2;
				stop = (i==0)? this.len/2 : this.len;
				t[i] = new Thread(new ThreadScalProd<>(this, Other, 0, this.len));
			}
			start = i*this.lenThreadVect;
			stop = (i*this.lenThreadVect) + this.lenThreadVect-1;
			t[i] = new Thread(new ThreadScalProd<>(this, Other, start, stop));
			t[i].start();
		}
		for(int i=0;i<this.nbrthread;i++){
			try {
				t[i].join();
			}
			catch (InterruptedException e){
					e.printStackTrace();
			}
		}
	}

	public void CalculVectSum(Vect0<T> Other){
		/*Launch vector sum in multi-threading*/
		int start, stop;
		Thread t[] = new Thread[this.nbrthread];
		for(int i = 0; i<nbrthread;i++){
			start = i*this.lenThreadVect;
			stop = (i*this.lenThreadVect) + this.lenThreadVect-1;
			t[i] = new Thread(new ThreadVectSum<>(this, Other, start, stop));
			t[i].start();
		}
		for(int i=0;i<this.nbrthread;i++){
			try {
				t[i].join();
			}
			catch (InterruptedException e){
					e.printStackTrace();
			}
		}
	}

	private void setNbrThread(){
		/*Determine number of thread(smaller than MAXTHREAD) for VectSum
		 * and ScalProd method following the length of the vect*/
		boolean UnderMaxThread = false;
		this.lenThreadVect = 10;
		while (!UnderMaxThread){
			if (this.len > 5 && this.len <= 20){
				this.nbrthread = 2;
				UnderMaxThread = true;
			}
			else if (this.len > 20){
				this.nbrthread = (this.len/this.lenThreadVect)+
						((this.len%this.lenThreadVect >0) ? 1 : 0);

				if(2*this.nbrthread <= MAXTHREAD)
					{UnderMaxThread = true;}
			}
			else {
				this.nbrthread = 1;
				UnderMaxThread = false;
			}
			this.lenThreadVect++;
		}
	}

	public void setVectElem(int i, T elem){
		try {
		 this.vect[i] = elem;
		 } catch (Exception e) {
			 e.printStackTrace();
		 }
	}

	public synchronized void setScalprod(T prod){
		this.product = ScalSum(this.product, prod);
	}

	@SuppressWarnings("unchecked")
	private T ScalSum(T dest, T src) {
		if (src instanceof Integer){
			return (T)(Integer) (dest.intValue()+ src.intValue());
		}
		else if (src instanceof Long) {
			return (T)(Long) (dest.longValue()+ src.longValue());
		}
		else if (src instanceof Short) {
			return (T)(Integer) (dest.shortValue()+ src.shortValue());
		}
		else if (src instanceof Byte) {
			return (T)(Integer) (dest.byteValue()+ src.byteValue());
		}
		else if (src instanceof Double) {
			return (T)(Double) (dest.doubleValue()+ src.doubleValue());
		}
		else if (src instanceof Float) {
			return (T)(Float) (dest.floatValue()+ src.floatValue());
		}
		else {throw new UnsupportedOperationException("Unknown type");}
	}

	public T getVect(int i){return this.vect[i];}

	public int getlength(){return this.len;}

	public T[] getVect(){return this.vect;}

	public T getProduct(){return this.product;}

	public String getStrVect(){return Arrays.toString(this.vect);}

	@SuppressWarnings("hiding")
	private class ThreadScalProd<T extends Number> implements Runnable{
		/*Handle the scalar product of two Vect0 by creating a thread
		 *for a chunk of the array*/
			private Vect0<T> Vector;
			private Vect0<T> Other;
			private int start;
			private int stop;

			public ThreadScalProd(Vect0<T> Vector, Vect0<T> Other, int start, int stop){
				this.Vector = Vector;
				this.Other = Other;
				this.start = start;
				this.stop = stop;
			}

			@SuppressWarnings("unchecked")
			public void run() {
				//thread
				T prod = (T)(Integer)(0);
				if (this.Vector.getlength() == this.Other.getlength()){
					for(int i=start; i< this.Vector.getlength() && i<= stop;i++){
						prod = Sum(prod, mul(Vector.getVect(i), Other.getVect(i)));
					}
					Vector.setScalprod(prod);
				} else {
					System.out.println("Les vecteurs n'ont pas la même taille et le même type");
				}
			}

			@SuppressWarnings("unchecked")
			private T mul(T x, T y) {
				if (x instanceof Integer) {
					return (T)(Integer)(x.intValue()*y.intValue());
				}
				else if (x instanceof Double) {
					return (T)(Double)(x.doubleValue()*y.doubleValue());
				}

				else if (x instanceof Long) {
					return (T)(Long)(x.longValue()*y.longValue());
				}
				else if (x instanceof Short) {
					return (T)(Integer)(x.shortValue()*y.shortValue());
					}
				else if (x instanceof Byte) {
					return (T)(Integer)(x.byteValue()*y.byteValue());
				}
				else if (x instanceof Float) {
					return (T)(Float)(x.floatValue()*y.floatValue());
				}
				else {
					return null;
				}
			}

			@SuppressWarnings("unchecked")//avoid warnings about cast
			private T Sum(T dest, T src) {
				if (src instanceof Integer){
					return (T)(Integer) (dest.intValue()+ src.intValue());
				}
				else if (src instanceof Long) {
					return (T)(Long) (dest.longValue()+ src.longValue());
				}
				else if (src instanceof Short) {
					return (T)(Short)(short)(dest.shortValue()+ src.shortValue());
				}
				else if (src instanceof Byte) {
					return (T)(Byte)(byte)(dest.byteValue()+ src.byteValue());
				}
				else if (src instanceof Double) {
					return (T)(Double) (dest.doubleValue()+ src.doubleValue());
				}
				else if (src instanceof Float) {
					return (T)(Float) (dest.floatValue()+ src.floatValue());
				}
				else {
				throw new UnsupportedOperationException("Unknown type");
			}
		}
	}

	@SuppressWarnings("hiding") // suppress The type parameter T is hiding the type T
	private class ThreadVectSum<T extends Number> implements Runnable {
		/*Handle the vector sum of two Vect0 by creating a thread
		 *for a chunk of the array*/
		private Vect0<T> Vector;
		private Vect0<T> Other;
		private int start;
		private int stop;

		private ThreadVectSum(Vect0<T> Vector, Vect0<T> Other, int start, int stop){
			this.Vector = Vector;
			this.Other = Other;
			this.start = start;
			this.stop = stop;
		}

		public void run() {
			// thread
			for(int i = this.start;i<this.Vector.getlength() && i<= this.stop;i++){
				Vector.setVectElem(i, add(Vector.getVect(i), Other.getVect(i)));
			}
		}

		@SuppressWarnings("unchecked")
		private T add(T dest, T src) {
			if (dest instanceof Integer) {
				return (T)(Integer)(dest.intValue()+src.intValue());
			}
			else if (dest instanceof Double) {
				return (T)(Double)(dest.doubleValue()+src.doubleValue());
			}
			else if (dest instanceof Long) {
				return (T)(Long)(dest.longValue()+src.longValue());
			}
			else if (dest instanceof Short) {
				return (T)(Short)(short)(dest.shortValue()+src.shortValue());
			}
			else if (dest instanceof Byte) {
				return (T)(Byte)(byte)(dest.byteValue()+src.byteValue());
			}
			else if (dest instanceof Float) {
				return (T)(Float)(dest.floatValue()+src.floatValue());
			}
			else {
				return null;
			}
		}
	}
}
