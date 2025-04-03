Action()
{

/*

Updated: 04.2025
Script created by Salvador Camacho

This script has the same steps as AOS-Web-S01 Browse Abandon, but this one simulates the http Mobile traffic, which would get recorded
from an actual mobile device with VuGen proxy recorder

This script was created with best practices, so it is more resilient, such as:
* Transaction naming
* No add cookies
* No third party
* One validation per transaction
* Think times at the end of each transaction to better simulate user behavior
* Main URL parametrized, Public AOS by default

This script randomly selects a product from the category and then goes to it in transaction number 3 and adds it to the cart to then abandon the cart
The Add To Cart step is "simulated" (it hits a random AOS product image) as there is no http traffic in AOS when adding to the cart

Runtime Settings were set to log only on errors and generate snapshot on errors, think times 75% to 150%

This script has 5 transactions
AOS-Web-Mobile HTTP Traffic-S01-01 Access AOS URL
AOS-Web-Mobile HTTP Traffic-S01-02 Go To Speakers
AOS-Web-Mobile HTTP Traffic-S01-03 Random Product
AOS-Web-Mobile HTTP Traffic-S01-04 Add To Cart
AOS-Web-Mobile HTTP Traffic-S01-05 Checkout

*/
	
	web_set_sockets_option("SSL_VERSION", "AUTO");
	
	web_reg_save_param_json(
		"ParamName=productId",
		"QueryString=$..products..productId",
		"SelectAll=Yes",
		LAST);

lr_start_transaction("AOS-Web-Mobile HTTP Traffic-S01-01 Laptops");

	web_url("products", 
		"URL={AOS_URL}/catalog/api/v1/categories/1/products", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={AOS_URL}/", 
		"Snapshot=t24.inf", 
		"Mode=HTML", 
		LAST);

	web_url("attributes", 
		"URL={AOS_URL}/catalog/api/v1/categories/attributes", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={AOS_URL}/", 
		"Snapshot=t25.inf", 
		"Mode=HTML", 
		LAST);
		
	web_reg_find("Text=category-type-products", 
		LAST);

	web_url("category-page.html", 
		"URL={AOS_URL}/app/views/category-page.html", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={AOS_URL}/", 
		"Snapshot=t26.inf", 
		"Mode=HTML", 
		LAST);

lr_end_transaction("AOS-Web-Mobile HTTP Traffic-S01-01 Laptops",LR_AUTO);

	lr_think_time(10);
	
	
	// Random Value for productId
	lr_save_string(lr_paramarr_random("productId"),"randomProductId");

lr_start_transaction("AOS-Web-Mobile HTTP Traffic-S01-02 Product");

	web_url("randomProduct", 
		"URL={AOS_URL}/catalog/api/v1/products/{randomProductId}", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={AOS_URL}/", 
		"Snapshot=t27.inf", 
		"Mode=HTML", 
		LAST);

	web_url("all_data", 
		"URL={AOS_URL}/catalog/api/v1/categories/all_data", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={AOS_URL}/", 
		"Snapshot=t28.inf", 
		"Mode=HTML", 
		LAST);

	web_url("products_2", 
		"URL={AOS_URL}/catalog/api/v1/categories/4/products", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={AOS_URL}/", 
		"Snapshot=t29.inf", 
		"Mode=HTML", 
		LAST);
		
	web_reg_find("Text=productProperties", 
		LAST);

	web_url("product-page.html", 
		"URL={AOS_URL}/app/views/product-page.html", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={AOS_URL}/", 
		"Snapshot=t30.inf", 
		"Mode=HTML", 
		LAST);

lr_end_transaction("AOS-Web-Mobile HTTP Traffic-S01-02 Product",LR_AUTO);

	lr_think_time(10);


lr_start_transaction("AOS-Web-Mobile HTTP Traffic-S01-03 Add To Cart");

	web_url("AddToCart",
		"URL={AOS_URL}/catalog/fetchImage?image_id={image_id}",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
		LAST);

lr_end_transaction("AOS-Web-Mobile HTTP Traffic-S01-03 Add To Cart",LR_AUTO);

	lr_think_time(10);
	
	
	web_reg_find("Text=<article id=\"our_products\">", 
		LAST);

lr_start_transaction("AOS-Web-Mobile HTTP Traffic-S01-04 Home");

	web_url("home-page.html", 
		"URL={AOS_URL}/app/views/home-page.html", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={AOS_URL}/", 
		"Snapshot=t31.inf", 
		"Mode=HTML", 
		LAST);

lr_end_transaction("AOS-Web-Mobile HTTP Traffic-S01-04 Home",LR_AUTO);

	lr_think_time(10);


	return 0;
}