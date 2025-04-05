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

This script has 5 transactions:  
AOS-Web-Mobile HTTP Traffic-S01-01 Access AOS URL  
AOS-Web-Mobile HTTP Traffic-S01-02 Go To Speakers  
AOS-Web-Mobile HTTP Traffic-S01-03 Random Product  
AOS-Web-Mobile HTTP Traffic-S01-04 Add To Cart  
AOS-Web-Mobile HTTP Traffic-S01-05 Checkout