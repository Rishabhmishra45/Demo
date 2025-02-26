document.addEventListener("DOMContentLoaded", function () {
    const cart = [];
    const cartItemsList = document.getElementById("cart-items");
    const totalAmount = document.getElementById("total");
    const addToCartButtons = document.querySelectorAll(".add-to-cart");

    addToCartButtons.forEach(button => {
        button.addEventListener("click", function () {
            const itemName = this.getAttribute("data-name");
            const itemPrice = parseFloat(this.getAttribute("data-price"));

            addToCart(itemName, itemPrice);
        });
    });

    function addToCart(name, price) {
        const existingItem = cart.find(item => item.name === name);

        if (existingItem) {
            existingItem.quantity += 1;
        } else {
            cart.push({ name, price, quantity: 1 });
        }

        updateCart();
    }

    function updateCart() {
        cartItemsList.innerHTML = "";
        let total = 0;

        cart.forEach(item => {
            total += item.price * item.quantity;

            const li = document.createElement("li");
            li.innerHTML = `${item.name} - $${item.price} x ${item.quantity} 
                <button class="remove-item" data-name="${item.name}">Remove</button>`;
            cartItemsList.appendChild(li);
        });

        totalAmount.textContent = total;

        document.querySelectorAll(".remove-item").forEach(button => {
            button.addEventListener("click", function () {
                removeFromCart(this.getAttribute("data-name"));
            });
        });
    }

    function removeFromCart(name) {
        const index = cart.findIndex(item => item.name === name);
        if (index !== -1) {
            if (cart[index].quantity > 1) {
                cart[index].quantity -= 1;
            } else {
                cart.splice(index, 1);
            }
        }
        updateCart();
    }
});
