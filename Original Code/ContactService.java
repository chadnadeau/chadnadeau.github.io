// Chad Nadeau

package contact;

import java.util.HashMap;
import java.util.Map;

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
        if (!contacts.containsKey(contactId)) {
            throw new IllegalArgumentException("Contact with ID " + contactId + " does not exist.");
        }

        if (firstName.length() > 10) {
            throw new IllegalArgumentException("Invalid first name: must be at most 10 characters.");
        }

        Contact contact = contacts.get(contactId);
        contact.setFirstName(firstName);
    }

    public void updateContactLastName(String contactId, String lastName) {
        if (!contacts.containsKey(contactId)) {
            throw new IllegalArgumentException("Contact with ID " + contactId + " does not exist.");
        }

        if (lastName.length() > 10) {
            throw new IllegalArgumentException("Invalid last name: must be at most 10 characters.");
        }

        Contact contact = contacts.get(contactId);
        contact.setLastName(lastName);
    }

    public void updateContactPhone(String contactId, String number) {
        if (!contacts.containsKey(contactId)) {
            throw new IllegalArgumentException("Contact with ID " + contactId + " does not exist.");
        }

        if (number == null || !number.matches("\\d{10}")) {
            throw new IllegalArgumentException("Invalid phone number: must be a non-null string of exactly 10 digits.");
        }

        Contact contact = contacts.get(contactId);
        contact.setPhone(number);
    }

    public void updateContactAddress(String contactId, String address) {
        if (!contacts.containsKey(contactId)) {
            throw new IllegalArgumentException("Contact with ID " + contactId + " does not exist.");
        }

        if (address.length() > 30) {
            throw new IllegalArgumentException("Invalid address: must be at most 30 characters.");
        }

        Contact contact = contacts.get(contactId);
        contact.setAddress(address);
    }
}