document.addEventListener('DOMContentLoaded', function() {
    // Create modal element
    const modal = document.createElement('div');
    modal.className = 'modal';
    modal.innerHTML = `
        <span class="modal-close">&times;</span>
        <img class="modal-content">
    `;
    document.body.appendChild(modal);

    const modalImg = modal.querySelector('.modal-content');
    const closeBtn = modal.querySelector('.modal-close');

    // Add click handlers to all grid images
    document.querySelectorAll('.grid-container img').forEach(img => {
        img.onclick = function() {
            modal.style.display = 'block';
            modalImg.src = this.src;
        }
    });

    // Close modal when clicking close button or outside the image
    closeBtn.onclick = function() {
        modal.style.display = 'none';
    }
    modal.onclick = function(e) {
        if (e.target === modal) {
            modal.style.display = 'none';
        }
    }

    // Close modal with escape key
    document.addEventListener('keydown', function(e) {
        if (e.key === 'Escape' && modal.style.display === 'block') {
            modal.style.display = 'none';
        }
    });
});