// ContactService-Enhanced.java
// Author: Chad Nadeau

package contact;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class ContactService {

    private Map<String, Contact> contacts;

    public ContactService() {
        contacts = new HashMap<>();
    }

    public void addContact(Contact contact) {
        if (contacts.containsKey(contact.getContactID())) {
            throw new IllegalArgumentException("Contact with ID " + contact.getContactID() + " already exists.");
        }
        contacts.put(contact.getContactID(), contact);
    }

    public Contact getContactByID(String id) {
        return contacts.get(id);
    }

    public void deleteContact(String id) {
        if (!contacts.containsKey(id)) {
            throw new IllegalArgumentException("Contact with ID " + id + " does not exist.");
        }
        contacts.remove(id);
    }

    public void updateContactFirstName(String contactId, String firstName) {
        validateContactId(contactId);
        validateName(firstName, "First");
        Contact contact = contacts.get(contactId);
        contact.setFirstName(firstName);
    }

    public void updateContactLastName(String contactId, String lastName) {
        validateContactId(contactId);
        validateName(lastName, "Last");
        Contact contact = contacts.get(contactId);
        contact.setLastName(lastName);
    }

    public void updateContactPhone(String contactId, String number) {
        validateContactId(contactId);
        validatePhoneNumber(number);
        Contact contact = contacts.get(contactId);
        contact.setPhone(number);
    }

    public void updateContactAddress(String contactId, String address) {
        validateContactId(contactId);
        validateAddress(address);
        Contact contact = contacts.get(contactId);
        contact.setAddress(address);
    }

    // New method to search contacts by name (first or last)
    public List<Contact> searchContacts(String searchTerm) {
        if (searchTerm == null || searchTerm.isEmpty()) {
            throw new IllegalArgumentException("Search term cannot be null or empty.");
        }

        // Case-insensitive search
        return contacts.values().stream()
            .filter(contact -> contact.getFirstName().toLowerCase().contains(searchTerm.toLowerCase()) ||
                              contact.getLastName().toLowerCase().contains(searchTerm.toLowerCase()))
            .collect(Collectors.toList());
    }

    // New method to filter contacts by phone number
    public List<Contact> filterContactsByPhone(String phoneNumber) {
        if (phoneNumber == null || phoneNumber.isEmpty()) {
            throw new IllegalArgumentException("Phone number cannot be null or empty.");
        }

        return contacts.values().stream()
            .filter(contact -> contact.getPhone().equals(phoneNumber))
            .collect(Collectors.toList());
    }

    // Validation methods
    private void validateContactId(String contactId) {
        if (!contacts.containsKey(contactId)) {
            throw new IllegalArgumentException("Contact with ID " + contactId + " does not exist.");
        }
    }

    private void validateName(String name, String type) {
        if (name == null || name.length() > 10) {
            throw new IllegalArgumentException("Invalid " + type + " name: must be a non-null string of at most 10 characters.");
        }
    }

    private void validatePhoneNumber(String number) {
        if (number == null || !number.matches("\\d{10}")) {
            throw new IllegalArgumentException("Invalid phone number: must be a non-null string of exactly 10 digits.");
        }
    }

    private void validateAddress(String address) {
        if (address == null || address.length() > 30) {
            throw new IllegalArgumentException("Invalid address: must be a non-null string of at most 30 characters.");
        }
    }
}