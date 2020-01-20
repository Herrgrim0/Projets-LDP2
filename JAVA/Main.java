/* Langages de programmation 2 - Projet java
 * GRIMAU Romain
 * 000440048
 * 16/08/2018
 */

public class Main {
	public static void main(String[] args) {
	
		System.out.println("Utilisation du type long:");
		Long[] ve = {12L, 45L, 98L, 62L, 54L, 32L, 12L, 45L, 87L, 65L, 95L, 22L, 45L, 684L, 78L, 51L, 93L, 25L, 10L, 20L, 24L, 23L, 21L, 75L};
		Long[] v2 = {45L, 78L, 98L ,41L, 23L, 69L, 55L, 12L, 45L, 98L, 62L, 54L, 32L, 127L, 45L, 87L, 65L, 95L, 22L, 45L, 4L, 52L, 32L, 44L};
		Vect0<Long> Lvect0 = new Vect0<>(v2);
		Vect0<Long> Lvect1 = new Vect0<>(ve);
		System.out.println("Vecteur avant produit scalaire: "+Lvect0.getStrVect());
		System.out.println("Vecteur avant produit scalaire: "+Lvect1.getStrVect());
		Lvect1.CalculScalProd(Lvect0);
		Lvect1.CalculVectSum(Lvect0);
		System.out.println("Vecteur après le produit scalaire: "+Lvect1.getProduct());
		System.out.println("La somme vectorielle: "+Lvect1.getStrVect());
		System.out.println("==================================================\n");
		
		System.out.println("Utilisation du type integer:");
		Integer[] v3 = {12, 45, 98, 62, 54, 32, 12, 45, 87};
		Integer[] v4 = {45, 78, 98 ,41, 23, 69, 55, 12, 44};
		Vect0<Integer> Ivect0 = new Vect0<>(v3);
		Vect0<Integer> Ivect1 = new Vect0<>(v4);
		System.out.println("Vecteur avant produit scalaire: "+Ivect0.getStrVect());
		System.out.println("Vecteur avant produit scalaire: "+Ivect1.getStrVect());
		Ivect0.CalculScalProd(Ivect1);
		Ivect0.CalculVectSum(Ivect1);
		System.out.println("Vecteur après le produit scalaire: "+Ivect0.getProduct());
		System.out.println("La somme vectorielle: "+Ivect0.getStrVect());
		System.out.println("==================================================\n");
		
		System.out.println("Utilisation du type byte:");
		Byte[] v5 = {12, 45, 98, 62, 54, 32, 12, 45, 87, 127, -128, 65};
		Byte[] v6 = {45, 78, 98 ,41, 23, 69, 55, 12, 44, -75, 12, 42};
		Vect0<Byte> Bvect0 = new Vect0<>(v5);
		Vect0<Byte> Bvect1 = new Vect0<>(v6);
		System.out.println("Vecteur avant produit scalaire: "+Bvect0.getStrVect());
		System.out.println("Vecteur avant produit scalaire: "+Bvect1.getStrVect());
		Bvect0.CalculScalProd(Bvect1);
		Bvect0.CalculVectSum(Bvect1);
		System.out.println("Vecteur après le produit scalaire: "+Bvect0.getProduct());
		System.out.println("La somme vectorielle: "+Bvect0.getStrVect());
		System.out.println("==================================================\n");
		
		System.out.println("Utilisation du type Double:");
		Double[] v7 = {12.45, 45.02, 98.5, 62.00004, 54.132, 32.49, 12.24, 45.51, 87.6, 127.8, -128.59, 65.03, 0.265};
		Double[] v8 = {45.85, 78.6, 98.0 ,41.1, 23.0123, 69.69, 55.00, 12.2, 44.12, -75.62, 12.7, 42.27, 0.333};
		Vect0<Double> Dvect0 = new Vect0<>(v7);
		Vect0<Double> Dvect1 = new Vect0<>(v8);
		System.out.println("Vecteur avant produit scalaire: "+Dvect0.getStrVect());
		System.out.println("Vecteur avant produit scalaire: "+Dvect1.getStrVect());
		Dvect0.CalculScalProd(Dvect1);
		Dvect0.CalculVectSum(Dvect1);
		System.out.println("Vecteur après le produit scalaire: "+Dvect0.getProduct());
		System.out.println("La somme vectorielle: "+Dvect0.getStrVect());
		System.out.println("==================================================\n");

	}
}